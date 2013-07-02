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

void outb(u16 p, u8 d) {
  __asm__ volatile (
    "outb %%al, %%dx"
      :: "a"(d), "d"(p)
  );
}

u8 inb(u16 p) {
  u8 d=0;
  
  __asm__ volatile (
    "inb %%dx, %%al"
      : "=a"(d) : "d"(p)
  );
  
  return d;
}

void outw(u16 p, u16 d) {
  __asm__ volatile (
    "outw %%ax, %%dx"
      :: "a"(d), "d"(p)
  );
}

u16 inw(u16 p) {
  u16 d=0;
  
  __asm__ volatile (
    "inw %%dx, %%ax"
      : "=a"(d) : "d"(p)
  );
  
  return d;
}

void outl(u16 p, u32 d) {
  __asm__ volatile (
    "outl %%eax, %%dx"
      :: "a"(d), "d"(p)
  );
}

u32 inl(u16 p) {
  u32 d=0;
  
  __asm__ volatile (
    "inl %%dx, %%eax"
      : "=a"(d) : "d"(p)
  );
  
  return d;
}
