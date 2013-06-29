#include <mm/mm.h>
#include <mm/pmm.h>

u32 *stack_top;
u32 stack_size;

struct chunk {
  paddr_t start;
  paddr_t end;
  u32 size;
};

void test_chunk(struct chunk *chunk) {
  // region usable? (wiki: memory regions usable)
  
  // align
  
}

void pmm_setup(paddr_t mmap, u32 len) {
  struct chunk mem_chunks[32] = {0}; // guessing
  
  stack_size = 0;
  stack_top = NULL;
  
  // todo
}

u32 pmm_pop(void) {
  if(!stack_size) {
    return 0;
  }
  
  --stack_size;
  return *stack_top--;
}

void pmm_push(paddr_t page) {
  *++=stack_top = page;
  stack_size++;
}
