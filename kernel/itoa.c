#include <itoa.h>
#include <types.h>
#include <assert.h>

static const char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWYXZ";

u32 __divdi3(u64 v, u32 d) {
  u32 vl = v & 0xFFFFFFFF, vh = v >> 31;
  
  __asm__ (
    "div %%ebx"
      : "=d"(vh), "=a"(vl) : "b"(d)
  );
  
  return vl;
} 

u32 __moddi3(u64 v, u32 d) {
  u32 vl = v & 0xFFFFFFFF, vh = v >> 31;
  
  __asm__ (
    "div %%ebx"
      : "=d"(vh), "=a"(vl) : "b"(d)
  );
  
  return vh;
  
} 

char *itoa(i32 num, char *buf, u32 base)
{
  return ltoa(num, buf, base);
}

char *ltoa(i64 num, char *buf, u32 base)
{
  assert(buf != NULL);
  assert(base > 1 && base < 37);
  
  char *ptr = buf + 65;
  
  if (num >= 0) {
    do {
      *--ptr = digits[num % base];
      num /= base;
    } while (num);
  } else {
    num = -num;
    
    do {
      *--ptr = digits[num % base];
      num /= base;
    } while (num);
    
    *--ptr = '-';
  }
  
  return ptr;
}
