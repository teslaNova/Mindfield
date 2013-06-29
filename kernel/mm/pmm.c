#include <mm/mm.h>
#include <mm/pmm.h>

#include <types.h>
#include <multiboot.h>

// currently 32-bit only

volatile u32 *stack_top;
volatile u32 stack_size;

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

void pmm_setup(paddr_t mmap, u32 len) {
  struct chunk mem_chunks[CHUNKS] = {0}; // guessing
  memory_map_t *mmap_it = (memory_map_t *)mmap;
  u32 i=0, j, n, tmp_stack_size = 0;
  
  stack_size = 0;
  stack_top = (u32 *)MEMREG_PHYS_PMM_STACK_START;
  
  if(mmap == 0 || len == 0) {
    // panic();
    return;
  }
  
  while((u32)mmap_it < mmap+len && i < CHUNKS) {
    if(mmap_it->size != 0) {
      mem_chunks[i].start = ALIGN_UP(mmap_it->base_addr_low);
      mem_chunks[i].end = ALIGN_DOWN(mmap_it->base_addr_low + mmap_it->length_low);
      mem_chunks[i].size = (mem_chunks[i].end - mem_chunks[i].start);
      
      j = i;
      
      test_chunk(mem_chunks, &j, MEMREG_PHYS_KERNEL_START, MEMREG_PHYS_KERNEL_END);
      test_chunk(mem_chunks, &j, MEMREG_PHYS_VIDEO_START, MEMREG_PHYS_VIDEO_END);
      
      while(i < j) {
        tmp_stack_size += mem_chunks[i++].size / PAGE_SIZE;
      }
      
      FIND_EMPTY_CHUNK(mem_chunks, i);
    }
    
    mmap_it = mmap_it + mmap_it->size + sizeof(mmap_it->size);
  }

  for(i=0; i<CHUNKS; i++) {
    if(mem_chunks[i].size == 0) {
      continue;
    }
    
    j=i;
    test_chunk(mem_chunks, &j, MEMREG_PHYS_PMM_STACK_START, MEMREG_PHYS_PMM_STACK_END(tmp_stack_size * PAGE_SIZE));
    
    for(j=0, n=mem_chunks[i].size / PAGE_SIZE; j<n; j++) {
      *stack_top++ = mem_chunks[i].start + (j * PAGE_SIZE);
      stack_size ++;
    }
  }
}

u32 pmm_pop(void) {
  if(!stack_size) {
    return 0;
  }
  
  --stack_size;
  return *stack_top--;
}

void pmm_push(paddr_t page) {
  *++stack_top = page;
  stack_size++;
}
