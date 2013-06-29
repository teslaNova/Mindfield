#ifndef MM_MM_H_
#define MM_MM_H_

#include <types.h>

// memory management constants
#define PAGE_SIZE 4096

#define ALIGN_UP(x) x + (PAGE_SIZE - x % PAGE_SIZE) // optimize: bit-op only
#define ALIGN_DOWN(x) x - x % PAGE_SIZE // optimize: bit-op only

// memory regions by default
extern const void *KERNEL_START;
extern const void *KERNEL_END;

#define MEMREG_PHYS_KERNEL_START ((u32)(KERNEL_START))
#define MEMREG_PHYS_KERNEL_END ((u32)(KERNEL_END))

#define MEMREG_PHYS_VIDEO_START 0xB8000
#define MEMREG_PHYS_VIDEO_END MEMREG_PHYS_VIDEO_START + ALIGN_UP(80 * 25 * 2)

#define MEMREG_PHYS_PMM_STACK_START ALIGN_UP(MEMREG_PHYS_KERNEL_END) + PAGE_SIZE
#define MEMREG_PHYS_PMM_STACK_END(x) x + MEMREG_PHYS_PMM_STACK_START

#endif /* MM_MM_H_ */
