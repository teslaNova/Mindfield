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
  paddr_t baddr : 20;
  u16 pages : 12;
} bmd_entry;

/*typedef struct {
  union {
    paddr_t base_addr : 20;
    u16 id : 11;
    u8 type : 1;
    
    u32 raw;
  };
} raddr_t;*/
                    
#define BMT_GET_ENTRY(addr) bm[/* abs */(PAGE_ABS(addr) / (PAGE_SIZE * sizeof(bm_entry) * 8)]
#define BMT_ENTRY_SIZE_UNUSED(i) (bm[i].mask & (1 << 7) +\
                                                        bm[i].mask & (1 << 6) +\
                                                        bm[i].mask & (1 << 5) +\
                                                        bm[i].mask & (1 << 4) +\
                                                        bm[i].mask & (1 << 3) +\
                                                        bm[i].mask & (1 << 2) +\
                                                        bm[i].mask & (1 << 1) +\
                                                        bm[i].mask & (1 << 0))
                                                        
#ifdef ARCH_X86
#define BMT_SIZE PAGE_ABS (((u32)-1) / (PAGE_SIZE  * 8))
#elif defined(ARCH_X64)
//#define BMT_SIZE PAGE_ABS (((u64)-1) / (PAGE_SIZE  * 8))
#endif

void pmm_setup(paddr_t mmap, u32 len);

paddr_t pmm_alloc(void);
paddr_t pmm_alloc_m(u32 pc);

void pmm_free(paddr_t baddr);
void pmm_free_m(paddr_t baddr, u32 pc);

u32 pmm_size(void);

#endif /* MM_PMM_H_ */
