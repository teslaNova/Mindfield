#include <itoa.h>
#include <types.h>
#include <assert.h>

static const char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWYXZ";

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

void itoa_b(i32 num, char *buf, u32 base) 
{  
  ltoa_b(num, buf, base);
}

void ltoa_b(i64 num; char *buf; u32 base)
{
  assert(buf != NULL);
  assert(base > 1 && base < 37);
  
  char tmp[65];  
  register u32 off = 0;
  
  if (num >= 0) {
    do {
      tmp[off++] = digits[num % base];
      num /= base;
    } while (num);
  } else {
    num = -num;
    
    do {
      tmp[off++] = digits[num % base];
      num /= base;
    } while (num);
    
    *buf++= '-';
  }
  
  while (off > 0) {
    *buf++ = tmp[--off];
  }
}

