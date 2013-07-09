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

  for(i=0; i<CHUNKS; i++) {
   if(regs[i].size < PAGE_SIZE) {
     continue;
   }
 
   pc += regs[i].size / PAGE_SIZE;
   uc++;
  }

  uc += 1; // puffer, pmm region might be in a chunk
  total_size = ALIGN_UP(uc * sizeof(bmd_entry) + (pc / 8 + (pc % 8 > 0 ? 1 : 0)) * sizeof(bm_entry));

  for(i=0; i<CHUNKS; i++) {
   if(regs[i].size < PAGE_SIZE) {
     continue;
   }
 
   test_chunk(regs, i, MEMREG_PHYS_PMM_START, MEMREG_PHYS_PMM_END(total_size));
  }

  desc.tbl = MEMREG_PHYS_PMM_START;
  map.tbl = MEMREG_PHYS_PMM_START + sizeof(bmd_entry) * uc;

  for(i=0, j=0; i<CHUNKS && j<uc; i++) {
   if(regs[i].size < PAGE_SIZE) {
     continue;
   }
 
   desc.tbl[i].pages = regs[i].size / PAGE_SIZE;
   desc.tbl[i].baddr = regs[i].start;
 
   j++;
  }

  desc.entries = j;

  memset(map.tbl, 0xFF, (pc / 8 + (pc % 8 > 0 ? 1 : 0)) * sizeof(bm_entry));
  memset(map.tbl + pc / 8, (1 << pc % 8) - 1, sizeof(bm_entry));
}

paddr_t inline pmm_alloc(void) {
  return pmm_alloc_m(1);
}

paddr_t pmm_alloc_m(u32 pc) {
  return 0;
}

void inline pmm_free(paddr_t baddr) {
  pmm_free_m(baddr, 1);
}

void pmm_free_m(paddr_t baddr, u32 pc) {
  
}

u32 pmm_size(void) { // todo: calc real size (used, unused)
  return total_size;
}
