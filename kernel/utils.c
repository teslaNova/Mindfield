#include <utils.h>

/* todo: 
  cpu-check: sseX */

void *memcpy(void *dest, const void *src, u32 n) {
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
  while(t && n--) {
    if(*(u8*)t++ == (u8)(v & 0x0FF)) {
      return t;
    }
  }
  
  return NULL;
}

void *memset(void *dest, u32 v, u32 n) {
  while(dest && n--) {
    *(u8*)dest++ = (u8)(v & 0x0FF);
  }
  
  return dest;
}

void outb(u8 p, u8 d) {
  __asm__ volatile (
    "mov $0, %%dx;"
    "mov $1, %%si;"
    "outsb"
      :: "g"(p), "g"(d)
  );
}

u8 inb(u8 p) {
  u8 d=0;
  
  __asm__ volatile (
    "mov $1, %%dx;"
    "mov $0, %%di;"
    "insb"
      : "=g"(d) : "g"(p) 
   );
  
  return d;
}

void outw(u8 p, u16 d) {
  __asm__ volatile (
    "mov $0, %%dx;"
    "mov $1, %%si;"
    "outsw"
      :: "g"(p), "g"(d)
  );
}

u16 inw(u8 p) {
  u16 d=0;
  
  __asm__ volatile (
    "mov $1, %%dx;"
    "mov $0, %%di;"
    "insw"
      : "=g"(d) : "g"(p) 
   );
 
  
  return d;
}
