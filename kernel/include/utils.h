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
void outb(u16 p, u8 d);
u8 inb(u16 p);

void outw(u16 p, u16 d);
u16 inw(u16 p);

void outl(u16 p, u32 d);
u32 inl(u16 p);

#endif /* UTILS_H_ */
