#include <printf.h>
#include <screen.h>
#include <types.h>
#include <varg.h>
#include <utils.h>

/* numeric output */
static void printn(i32, u16, bool);

/* numeric output with buffer-support */
static void sprintn(char*, *u32, i32, u16, bool);

/* copy string into buffer */
static void sprints(char*, *u32, char*);

void k_printf(const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  
  for (; *fmt != 0; ++fmt) {
    if (*fmt == '%' && *(fmt + 1) != 0) {
      switch (*++fmt) {
        case 's':
          k_scrn_puts(va_arg(ap, char*));
          break;
        
        case 'i':
        case 'd':
        case 'u':
        case 'x':
        case 'b':
          printn(va_arg(ap, i32), 
            *fmt == 'x' ? 16 : *fmt == 'b' ? 2 : 10, 
            *fmt == 'u' || *fmt == 'x' || *fmt == 'b');
          break;
          
        case 'c':
          k_scrn_putc(va_arg(ap, char));
          break;
          
        case 'p':
          assert(0);
          break;
      }
    } else {
      k_scrn_putc(fmt);
    }
  }
  
  va_end(ap);
}

u32 k_snprintf(char *buf, u32 len, const char *fmt, ...)
{
  u32 avl = len;
  
  va_list ap;
  va_start(ap, fmt);
  
  for (; *fmt != 0 && avl != 0; ++fmt) {
    if (*fmt == '%' && *(fmt + 1) != 0) {
      switch (*++fmt) {
        case 's':
          sprints(buf, &avl, va_arg(ap, char*));
          break;
        
        case 'i':
        case 'd':
        case 'u':
        case 'x':
        case 'b':
          sprintn(buf, &avl, va_arg(ap, i32), 
            *fmt == 'x' ? 16 : *fmt == 'b' ? 2 : 10, 
            *fmt == 'u' || *fmt == 'x' || *fmt == 'b');
          break;
          
        case 'c':
          *buf++ = va_arg(ap, char), --avl;
          break;
          
        case 'p':
          assert(0);
          break;
      }
    } else {
      *buf++ = *fmt, --avl;
    }
  }
  
  va_end(ap);
  return len - avl;
}

/* todo: implement printn, sprintn & sprints */
