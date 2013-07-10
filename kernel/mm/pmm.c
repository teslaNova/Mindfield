#include <mm/mm.h>
#include <mm/pmm.h>

#include <types.h>
#include <utils.h>

#include <printf.h>

#include <multiboot.h>

extern void panic(void);

// CHUNKS
struct chunk {
  paddr_t start;
  paddr_t end;
  u32 size;
};

#define CHUNKS 32

static void test_chunk(struct chunk chunks[CHUNKS], u32 i, u32 start, u32 end) {
  if(chunks[i].start < start) {
    if(chunks[i].end < start) {
      return;
    }
    
    if(chunks[i].end < end) {
      chunks[i].end = ALIGN_DOWN(start);
      chunks[i].size = chunks[i].end - chunks[i].start;
      
      if(chunks[i].size < PAGE_SIZE) {
        memset(&chunks[i], 0, sizeof(struct chunk));
      }
    } else if(chunks[i].end > end) {
      u32 j=i;
      
      while(j < CHUNKS && chunks[j++].size != 0);
      
      if(j == CHUNKS) {
        panic();
      }
      
      /*
                           start                   end
        chkstart      chkend               chkstart        chkend
        *----------*-------------*-----------*
                i                                              j
      */
      chunks[j].end = chunks[i].end;
      chunks[j].start = end;
      chunks[j].size = chunks[j].end - chunks[j].start;
      
      chunks[i].end = ALIGN_DOWN(start);
      chunks[i].size = chunks[i].end - chunks[i].start;
    }
  } else if(chunks[i].start > start) {
    if(chunks[i].start > end) {
      return;
    }
    
    if(chunks[i].end < end) {
      memset(&chunks[i], 0, sizeof(struct chunk));
    } else if(chunks[i].end > end) {
      chunks[i].start = end;
      chunks[i].size = chunks[i].end - chunks[i].start;
      
      if(chunks[i].size < PAGE_SIZE) {
        memset(&chunks[i], 0, sizeof(struct chunk));
      }
    }
  }
}


// BIT & DESCRIPTION MAP
#define DEF_CONTAINER(name, type) static struct {type* tbl; u32 entries;} name;

DEF_CONTAINER(desc, bmd_entry);
DEF_CONTAINER(map, bm_entry);
//DEF_CONTAINER(reserved, raddr_t);

static u32 total_size = 0;

void pmm_setup(paddr_t mmap_addr, u32 entries) { // todo: redo whole function. maybe also test_chunk.
  struct chunk regs[CHUNKS] = {0}; // guessing
  memory_map_t *mmap = (memory_map_t *) mmap_addr;
  u32 i, j, k, pc = 0, uc=0;

  memset(&desc, 0, sizeof(desc));
  memset(&map, 0, sizeof(map));

  if(mmap_addr == 0 || entries == 0) {
    panic();
    return;
  }

  /* collect useable regions provided through grub. 
    test_chunk()'ll split if protected regions (kernel, ..) if 
    necessary. */
  for(i=0, j=0; i<entries; i++) {
    if(mmap[i].length_low < PAGE_SIZE || mmap[i].base_addr_low == 0) {
      continue;
    }
  
    regs[j].start = ALIGN_UP(mmap[i].base_addr_low);
    regs[j].end = ALIGN_DOWN(mmap[i].base_addr_low + mmap[i].length_low);
    regs[j].size = regs[j].end - regs[j].start;
  
    test_chunk(regs, j, MEMREG_PHYS_KERNEL_START, MEMREG_PHYS_KERNEL_END);
    test_chunk(regs, j, MEMREG_PHYS_VIDEO_START, MEMREG_PHYS_VIDEO_END);
  
    ++j;
  }

  /* count total amount of pages and regions */
  for(i=0; i<CHUNKS; i++) {
   if(regs[i].size < PAGE_SIZE) {
     continue;
   }
 
   pc += regs[i].size / PAGE_SIZE;
   uc++;
  }

  /* calculate memory needed for pmm itself and treat it as protected */
  desc.entries = uc + 1; // puffer, pmm region might be in a chunk
  map.entries = (pc / 8 + (pc % 8 > 0 ? 1 : 0));

  total_size = ALIGN_UP(desc.entries * sizeof(bmd_entry) + map.entries * sizeof(bm_entry));

  for(i=0; i<CHUNKS; i++) {
   if(regs[i].size < PAGE_SIZE) {
     continue;
   }
 
   test_chunk(regs, i, MEMREG_PHYS_PMM_START, MEMREG_PHYS_PMM_END(total_size));
  }

  /* description and bitmap table init */
  desc.tbl = (bmd_entry *) (MEMREG_PHYS_PMM_START);
  map.tbl = (bm_entry *) (MEMREG_PHYS_PMM_START + sizeof(bmd_entry) * desc.entries);
  
  memset(desc.tbl, 0, desc.entries * sizeof(bmd_entry));

  for(i=0, j=0; i<CHUNKS && j<desc.entries; i++) {
   if(regs[i].size < PAGE_SIZE) {
     continue;
   }
 
   desc.tbl[j].pages = regs[i].size / PAGE_SIZE;
   desc.tbl[j].baddr = regs[i].start;
   
//   k_printf("0x%08x - 0x%08x | %08x pages\n", desc.tbl[j].baddr, desc.tbl[j].pages * PAGE_SIZE + desc.tbl[j].baddr, desc.tbl[j].pages);
 
   j++;
  }

  desc.entries = j;

  /* set active page bits */
  memset(map.tbl, 0xFF, map.entries * sizeof(bm_entry));

  if(pc % 8 != 0) {
     memset(map.tbl + (map.entries - 1) * sizeof(bm_entry), (1 << pc % 8) - 1, sizeof(bm_entry));
  } 
}

paddr_t inline pmm_alloc(void) {
  return pmm_alloc_m(1);
}

paddr_t pmm_alloc_m(u32 pc) {
  u32 pos = 0, i=0;
  u8 *mptr = NULL;
  paddr_t addr = 0;
  
  /* 
    mptr: base addr to first page found for allocation 
    i: description table index
    j: page index
    k: contiguous counter (free pages)
    pc: page count
    pos: offset to first page found for allocation
    n: local byte counter (table entry)
    off: byte counter (table entries)
  */
  for(u32 off=0, k=0; i<desc.entries; i++, k=0, mptr=NULL) { // todo: algo NOT optimized
    for(u32 j=(i == 0 ? 0 : desc.tbl[i - 1].pages % 8), n=0; j<desc.tbl[i].pages && k != pc; j++) {// byte offset incorrect
      if((j & 0x7) == 0 && j != 0) { // next byte?
        n++;
      }
      
      if(k == 0) { // restart counting.. set position and base address
        pos = j;
        mptr = (u8 *) map.tbl + off + n;
      }
      
      //k_printf("%x %x  ", *(u8 *)(map.tbl + off) , (*(u8 *)(map.tbl + off) & (1 << (j & 0x7))));
      
      if((*(u8 *)(map.tbl + off + n) & (1 << (j & 0x7))) == 0) { // check current bit if used (0) or free (1)
        k = 0;
      } else {
        k++;
      }
    }
    
    if(k == pc) { // pc pages found
      break;
    }
    
    off += desc.tbl[i].pages / 8;
  }
  
  if(mptr == NULL || i == desc.entries) {
    return 0;
  }
  
  addr = desc.tbl[i].baddr + (pos * PAGE_SIZE); // base addr calculation 
//  k_printf("\ndir: %x (pages: %04x), page: %08x, base addr: 0x%08x, addr: 0x%08x\n", i, desc.tbl[i].pages, pos, desc.tbl[i].baddr, addr);
  
  /*
    i: page counter
    j: bit offset
    mptr: ptr to bitmap
  */
  for(u32 i=0, j=pos & 0x7; i<pc; i++, j++) {
    if(j == 8) { // next byte?
      j = 0;
      mptr++;
    }
    
    *mptr = *mptr & (u8)~(1 << j); // unset bit
  }
  
  return addr;
}

void inline pmm_free(paddr_t baddr) {
  pmm_free_m(baddr, 1);
}

void pmm_free_m(paddr_t baddr, u32 pc) {
  u8 *mptr = (u8 *) map.tbl;

  /*
    mptr: ptr to bitmap
    i: descr. tbl. index
    j: bit/page offset/counter
    off: byte offset (bitmap)
    n: local byte offset
    pos: first page entry
    pc: page count
  */
  for(u32 i=0, off = 0; i<desc.entries; i++) {
    /* addr between region start / end? */
    if(baddr >= desc.tbl[i].baddr && baddr <= desc.tbl[i].baddr + desc.tbl[i].pages * PAGE_SIZE - 1 /* overlapping value */) {
      u32 pos = (baddr - desc.tbl[i].baddr) / PAGE_SIZE; // calc addr to bit position of the first entry
      
      for(u32 j=pos, n=0; j<pos+pc; j++) {
        if((j & 0x7) == 0 && j != 0) { // next byte?
          n++;
        }
        
//        k_printf("bm: %d %08b -> ",n, *(u8 *)(mptr + off + n));
        
        *(u8 *)(mptr + off + n) |= (u8)(1 << (j & 0x7)); // set bit
        
//        k_printf("%08b\n", *(u8 *)(mptr + off + n));
      }
      
      break;
    }
    
    off += desc.tbl[i].pages / 8;
  }
}

u32 pmm_size(void) { // todo: calc real size (used, unused)
  return total_size;
}
