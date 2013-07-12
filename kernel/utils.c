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

u32 read_cr(u8 reg) {
  u32 val = 0;
  
  switch(reg) {
    case 0: {
      __asm__ volatile (
        "mov %%cr0, %%eax"
          : "=a"(val)
      );
    } break;
    
    case 2: {
      __asm__ volatile (
        "mov %%cr2, %%eax"
          : "=a"(val)
      );
    } break;
    
    case 3: {
      __asm__ volatile (
        "mov %%cr3, %%eax"
          : "=a"(val)
      );
    } break;
    
    case 4: {
      __asm__ volatile (
        "mov %%cr4, %%eax"
          : "=a"(val)
      );
    } break;
  }
  
  return val;
}

void write_cr(u8 reg, u32 val) {
  switch(reg) {
    case 0: {
      __asm__ volatile (
        "mov %%eax, %%cr0"
          :: "a"(val)
      );
    } break;
    
    case 2: {
      __asm__ volatile (
        "mov %%eax, %%cr2"
          :: "a"(val)
      );
    } break;
    
    case 3: {
      __asm__ volatile (
        "mov %%eax, %%cr3"
          :: "a"(val)
      );
    } break;
    
    case 4: {
      __asm__ volatile (
        "mov %%eax, %%cr4"
          :: "a"(val)
      );
    } break;
  }
}

void inline cli(void) {
  __asm__ volatile ("cli");
}

void inline sti(void) {
  __asm__ volatile ("sti");
}

void inline hlt(void) {
  __asm__ volatile ("hlt");
}

void inline cpuid(u32 id, u32 *eax, u32 *ebx, u32 *ecx, u32 *edx) {
  register u32 ra __asm__ ("eax") = id;
  
  __asm__ volatile ("cpuid;"
    : "=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx));
}
