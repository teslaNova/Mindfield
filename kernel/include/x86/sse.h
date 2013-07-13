#ifndef X86_SSE_H_
#define X86_SSE_H_

#include <types.h>

void sse_init(void);

void *sse_memcpy(void *dest, const void *src, u32 n);
int sse_memcmp(void *l1, void *l2, u32 len);
const void *sse_memchr(const void *t, u32 v, u32 n);
void *sse_memset(void *dest, u32 v, u32 n);

#endif /* X86_SSE_H_ */
