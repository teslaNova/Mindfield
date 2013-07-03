#ifndef MM_PMM_H_
#define MM_PMM_H_

#include <types.h>

/* todo: paging switch for stack */

void pmm_setup(paddr_t mmap, u32 len);

u32 pmm_pop(void);
void pmm_push(paddr_t page);

u32 pmm_size(void);

#endif /* MM_PMM_H_ */
