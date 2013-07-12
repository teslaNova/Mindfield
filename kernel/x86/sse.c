#include <sse.h>

void *sse_memcpy(void *dest, const void *src, u32 n) {
  __asm__ volatile (
    ""
    : "=D"(dest) : "S"(src), "c"(n)
  );
  
  return dest;
}

int sse_memcmp(void *l1, void *l2, u32 len) {
  register int *eax __asm__ ("eax");
  
  __asm__ volatile (
    ""
    :: "D"(l1), "S"(l2), "c"(len)
  );
  
  return *eax;
}

const void *sse_memchr(const void *t, u32 v, u32 n) {
  register void *esi __asm__ ("esi") = (void *) t;
  
  __asm__ volatile (
    ""
    :: "m"(v), "c"(n)
  );
  
  return esi;
}

void *sse_memset(void *dest, u32 v, u32 n) {
  __asm__ volatile (
    ""
    : "=D"(dest) : "m"(v), "c"(n)
  );
  
  return dest;
}
