#ifndef UTILS_H_
#define UTILS_H_

#include <types.h>

/* memX */
void *memcpy(void *dest, const void *src, u32 n);
void *memmove(void *dest, const void *src, u32 n); 
int memcmp(void *l1, void *l2, u32 len);
const void *memchr(const void *t, u32 v, u32 n);
void *memset(void *dest, u32 v, u32 n);

/* port actions */
void outb(u8 p, u8 d);
u8 inb(u8 p);

void outw(u8 p, u16 d);
u16 inw(u8 p);

#endif /* UTILS_H_ */
