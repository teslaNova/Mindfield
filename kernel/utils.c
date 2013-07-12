#include <utils.h>
#include <cpu.h>

#ifdef ARCH_X86
#include <x86/sse.h>
#endif

void *memcpy(void *dest, const void *src, u32 n) {
#ifdef ARCH_X86
  if(cpu_get_bs()->sse >= 20) {
    return sse_memcpy(dest, src, n);
  }
#endif
  
  while(dest && src && n--) {
    *(u8*)dest++ = *(u8*)src++;
  }
  
  return dest;
}

void *memmove(void *dest, const void *src, u32 n) {
  memcpy(dest, src, n);
  return dest;
}

int memcmp(void *l1, void *l2, u32 len) {
#ifdef ARCH_X86
  if(cpu_get_bs()->sse >= 20) {
    return sse_memcmp(l1, l2, len);
  }
#endif
  
  while(l1 && l2 && len--) {
    if(*(u8*)l1 == *(u8*)l2) {
      l1++; l2++;
      continue;
    }
    
    if(*(u8*)l1 < *(u8*)l2) {
      return 1;
    }
    
    return -1;
  }
  
  return 0;
}

const void *memchr(const void *t, u32 v, u32 n) {
#ifdef ARCH_X86
  if(cpu_get_bs()->sse >= 20) {
    return sse_memchr(t, v, n);
  }
#endif
  
  while(t && n--) {
    if(*(u8*)t++ == (u8)(v & 0x0FF)) {
      return t;
    }
  }
  
  return NULL;
}

void *memset(void *dest, u32 v, u32 n) {
#ifdef ARCH_X86
  if(cpu_get_bs()->sse >= 20) {
    return sse_memset(dest, v, n);
  }
#endif
  
  while(dest && n--) {
    *(u8*)dest++ = (u8)(v & 0x0FF);
  }
  
  return dest;
}
