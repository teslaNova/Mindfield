#include <mm/mm.h>
#include <mm/pmm.h>

#include <types.h>
#include <utils.h>

#include <multiboot.h>

extern void panic(void);

// CHUNKS
struct chunk {
  paddr_t start;
  paddr_t end;
  u32 size;
};

#define CHUNKS 64

#define FIND_EMPTY_CHUNK(chunks, i) while(chunks[i].size != 0) { i++; }
#define CALC_CHUNK_SIZE(chunk) chunk.size = chunk.end - chunk.start

void test_chunk(struct chunk *chunks, u32 *i, u32 start, u32 end) {
  u32 tmp = 0;

  if(chunks[*i].start < start && chunks[*i].end > start) {
    if(chunks[*i].end < end) {
        chunks[*i].end = ALIGN_DOWN(start);
        CALC_CHUNK_SIZE(chunks[*i]);
    } else if(chunks[*i].end > end) {
      tmp = chunks[*i].end;
      chunks[*i].end = ALIGN_DOWN(start);
      CALC_CHUNK_SIZE(chunks[*i]);
      
      FIND_EMPTY_CHUNK(chunks, (*i));
      
      chunks[*i].start = ALIGN_UP(end);
      chunks[*i].end = tmp;
      CALC_CHUNK_SIZE(chunks[*i]);
    }
  }
  
  if(chunks[*i].start > start) {
    if(chunks[*i].end < end) {
      chunks[*i].start = 0;
      chunks[*i].end = 0;
      chunks[*i].size = 0;
    } else {
      chunks[*i].start = ALIGN_UP(end);
      CALC_CHUNK_SIZE(chunks[*i]);
    }
  }
}


// BIT & DESCRIPTION MAP
#define DEF_CONTAINER(name, type) static struct {type* tbl; u32 entries;} name;


DEF_CONTAINER(desc, bmd_entry);
DEF_CONTAINER(map, bm_entry);
//DEF_CONTAINER(reserved, raddr_t);

static u32 total_size = 0;

void pmm_setup(paddr_t mmap, u32 len) {
  struct chunk mem_chunks[CHUNKS] = {0}; // guessing
  memory_map_t *mmap_it = (memory_map_t *)mmap;
  u32 i=0, j, n, pc = 0, uc=0;
  
  memset(&desc, 0, sizeof(desc));
  memset(&map, 0, sizeof(map));
  
  if(mmap == 0 || len == 0) {
    panic();
    return;
  }
  
  while((u32)mmap_it < mmap+len && i < CHUNKS) {
    if(mmap_it->size != 0) {
      mem_chunks[i].start = ALIGN_UP(mmap_it->base_addr_low);
      mem_chunks[i].end = ALIGN_DOWN(mmap_it->base_addr_low + mmap_it->length_low);
      mem_chunks[i].size = (mem_chunks[i].end - mem_chunks[i].start);
      
      j = i;
      
      test_chunk(mem_chunks, &j, MEMREG_PHYS_KERNEL_START, MEMREG_PHYS_KERNEL_END);
      test_chunk(mem_chunks, &j, MEMREG_PHYS_VIDEO_START, MEMREG_PHYS_VIDEO_END); // textmode.. bga?
      
      while(i < j) {
        pc += mem_chunks[i++].size / PAGE_SIZE;
        
        if(pc) uc++;
      }
      
      FIND_EMPTY_CHUNK(mem_chunks, i);
    }
    
    mmap_it = mmap_it + mmap_it->size + sizeof(mmap_it->size);
  }
  
  desc.tbl = (bmd_entry *) MEMREG_PHYS_PMM_START;
  desc.entries = uc;
  
  map.tbl = (bm_entry *) (MEMREG_PHYS_PMM_START + (desc.entries * sizeof(bmd_entry)));
  map.entries = pc / 8 + pc % 8;
  
  total_size = ALIGN_UP(desc.entries * sizeof(bmd_entry) + map.entries * sizeof(bm_entry));
  
  for(i=0; i<CHUNKS; j=++i) {
    if(mem_chunks[i].size == 0) {
      continue;
    }
    
    test_chunk(mem_chunks, &j, MEMREG_PHYS_PMM_START, MEMREG_PHYS_PMM_END(total_size));
  }
  
  u32 mit = 0;
    
  for(i=0, j=0; i<CHUNKS; i++) {
    if(mem_chunks[i].size == 0) {
      continue;
    }
    
    desc.tbl[j].baddr = mem_chunks[i].start;
    desc.tbl[j].pages = mem_chunks[i].size / PAGE_SIZE;
    
    for(n=0; n<desc.tbl[j].pages; n++) {
      if(n & 0xFF) {
        mit++;
      }
      
      map.tbl[mit].mask |= 1 << (n & 0xFF);
    }
  }
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

u32 pmm_size(void) {
  return total_size / PAGE_SIZE;
}
