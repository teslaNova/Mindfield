#ifndef MM_MM_H_
#define MM_MM_H_

// memory management constants
#define PAGE_SIZE 4096

#define ALIGN_UP(x) x + (PAGE_SIZE - x % PAGE_SIZE) // optimize: bit-op only
#define ALIGN_DOWN(x) x - x % PAGE_SIZE // optimize: bit-op only

#endif /* MM_MM_H_ */
