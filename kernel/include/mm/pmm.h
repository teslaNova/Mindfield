#ifndef MM_PMM_H_
#define MM_PMM_H_

#include <types.h>

/* todo: paging switch for stack */

/* 
  thoughts:
  
    use bitmap-allocation and reservation vector
    with adresses reserved for tasks.
      
      reserved addr: 
    +----------------------+---------------+------------+
    | base addr (page aligned)   | thread or task id  | thread or task |
    +----------------------+---------------+------------+
      
      why?
    
        allow any process to allocate memory but do NOT map it
        at the same time. we don't know if the space allocated
        is used, so wait until the process wants to acess the 
        address and generates a #PF, then map it, or.. free it.

        bitmap-table: containing page states (used, unused)
        bitmap-descr-table: containing base addrs and amount of pages
*/
          
typedef struct {
  union {
    u8 ba0 : 1;
    u8 ba1 : 1;
    u8 ba2 : 1;
    u8 ba3 : 1;
    u8 ba4 : 1;
    u8 ba5 : 1;
    u8 ba6 : 1;
    u8 ba7 : 1;
    
    u8 mask;
  };
} bm_entry;

typedef struct {
  paddr_t baddr;
  u16 pages;
} bmd_entry;

/*typedef struct {
  union {
    paddr_t base_addr : 20;
    u16 id : 11;
    u8 type : 1;
    
    u32 raw;
  };
} raddr_t;*/

void pmm_setup(paddr_t mmap_addr, u32 entries);

paddr_t pmm_alloc(void);
paddr_t pmm_alloc_m(u32 pc);

void pmm_free(paddr_t baddr);
void pmm_free_m(paddr_t baddr, u32 pc);

u32 pmm_size(void);

#endif /* MM_PMM_H_ */
