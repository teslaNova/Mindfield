#include <stdbool.h>
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

#define i8 signed char
#define u8 unsigned char
#define i16 signed short
#define u16 unsigned short
#define i32 signed int
#define u32 unsigned int

/* printf implementation */
/* the syntax is (almost) the same as in stdio.h printf() [without support for float/double] */

/* needs some tests (!!!) */

/* formats:
   'c' --> character
   's' --> null-terminated string
   'd' --> signed 32bit number
   'i' --> signed 32bit number (alias of 'd')
   'x' --> unsigned 32bit number in hex lowercase notation
   'X' --> unsigned 32bit number in hex uppercase notation
   'u' --> unsigned 32bit number
   'b' --> unsigned 32bit number in binary notation
   'o' --> signed 32bit number in octal notation
   
   todo:
   'p' --> pointer
   
   planned:
   'l'  --> signed 64bit number
   'ld' --> signed 64bit number
   'lu' --> unsigned 64bit number
   'w'  --> multibyte character (UTF-32)
*/
   
/* flags: 
   '-' --> left-padding (default is right)
   '+' --> always print sign
   ' ' --> insert blank space if no sign is going to be written 
   '#' --> use prefix for numbers (0x for hex, 0b for binary or 0 for octal)
   '0' --> use 0 as padding instead of a blank space
   '=' --> use a custom padding (the next char defines the padding-char)
*/
   
/* width:
   NUMBER --> the given number (unsigned 32bit number [base 10]) is used as width
   '*'    --> the argument (unsigned 32bit number) preceding the argument that has to be formatted is used as width
*/ 

#define k_printf(fmt, args...) (void) k_snprintf(NULL, 0, fmt, args)
#define k_sprintf(buf, fmt, args...) k_snprintf(buf, 0, fmt, args)

typedef u16 pf_flags_t; /* space for 8 flags and one char (used for custom padding) */
typedef u32 pf_width_t;

#define FLAG_MASK 0b0000000011111111
#define FLAG_NONE 0b0000000000000000
#define FLAG_BPRX 0b0000000000000001
#define FLAG_LJUS 0b0000000000000010
#define FLAG_ASGN 0b0000000000000100
#define FLAG_NSGN 0b0000000000001000
#define FLAG_PNUL 0b0000000000010000
#define FLAG_PCUS 0b0000000000100000

/* handle "l" and "lu" format-types */
#define PF_HANDLE_LONG 0

/* handle 'w' (multibyte characters) */
#define PF_HANDLE_WIDE 0

/* check if a char is in 0..9 range (lazy macro) */
#define IS_DIGIT(c) ((c) >= '0' && (c) <= '9')

/* used in snprint_d */
static const char digits[] = "0123456789abcdefghijklmnopqrstuvwyxz"
                             "0123456789ABCDEFGHIJKLMNOPQRSTUVWYXZ";

/* format functions */
static void snprint_c(char*, u32, u32*, pf_flags_t, pf_width_t, char);
static void snprint_s(char*, u32, u32*, pf_flags_t, pf_width_t, char*);
static void snprint_d(char*, u32, u32*, pf_flags_t, pf_width_t, i32, char);

#if PF_HANDLE_LONG == 1
static void snprint_l(char*, u32, u32*, pf_flags_t, pf_width_t, i64, bool);
#endif

#if PF_HANDLE_WIDE == 1
static void snprint_w(char*, u32, u32*, pf_flags_t, pf_width_t, i32);
#endif

/* helper functions */
static void padd(char*, u32, u32*, pf_flags_t, pf_width_t);
static void outp(char*, u32, u32*, pf_flags_t, pf_width_t, char*, u32);

u32 k_snprintf(char *buf, u32 len, const char *fmt, ...)
{
  u32 off;
  va_list ap;
  
  va_start(ap, fmt);
  
  for (off = 0; *fmt != 0; ++off, ++fmt) {
    if (len > 0 && off >= len) {
      break;
    }
    
    if (*fmt == '%' && *(fmt + 1) != 0) {
      pf_flags_t flags = FLAG_NONE;
      pf_width_t width = 0;
      
      if (*++fmt == '%') {
        /* output a single '%' and continue */
        snprint_c(buf, len, &off, flags, width, '%');
        continue;
      }
      
      /* handle flags */
      for (bool acc = true; acc && *fmt;) {
        switch (*fmt) {
          default: acc = false; break;
          
          /* todo: check if a flag is already set? */
          case '-': flags |= FLAG_LJUS; break;
          case '+': flags |= FLAG_ASGN; break;
          case ' ': flags |= FLAG_NSGN; break;
          case '#': flags |= FLAG_BPRX; break;
          case '0': flags |= FLAG_PNUL; break;
          
          /* custom padding */
          case '=': 
            if (*(fmt + 1) == 0) {
              acc = false;
              break;
            }
            
            flags |= FLAG_PCUS;
            flags &= FLAG_MASK; /* clear previous char if any */
            flags |= (((u16) (*++fmt)) << 8) /* & ~FLAG_MASK */;
            break;
        }
        
        /* accept more flags */
        if (acc) ++fmt;
      }
      
      /* handle width */
      if (IS_DIGIT(*fmt)) {
        /* width is specified */
        u32 idx;
        const char *ptr = fmt;
        
        /* seek to the last valid digit in fmt */
        for (idx = 0; IS_DIGIT(*fmt); ++fmt, ++idx) ; /* noop */
        
        /* now walk back and compute */
        for (u32 pow = 1; idx > 0; pow *= 10, --idx) {
          width += (*(ptr + idx - 1) - '0') * pow;
        }
      } else if (*fmt == '*') {
        /* fetch number from arguments */
        width = va_arg(ap, u32);
      }
         
      switch (*fmt) {
        default: /* invalid format */
          /* todo: set errno or something? */
          goto done;
          
        /* char output */
        case 'c':
          snprint_c(buf, len, &off, flags, width, (char) va_arg(ap, i32));
          break;

#if PF_HANDLE_WIDE == 1
        /* multibyte output (UTF-32) */
        case 'w':
          snprint_w(buf, len, &off, flags, width, va_arg(ap, i32));
          break;
#endif 
/* if PF_HANDLE_WIDE == 1 */
       
        /* string output */
        case 's':
          snprint_s(buf, len, &off, flags, width, va_arg(ap, char*));
          break;
        
        /* decimal output */
        case 'd': /* signed 32bit number */
        case 'i': /* signed 32bit number */
        case 'x': /* hex lower */
        case 'X': /* hex upper */
        case 'u': /* unsigned 32bit number */
        case 'b': /* binary */
        case 'o': /* octal number */
          snprint_d(buf, len, &off, flags, width, va_arg(ap, i32), *fmt);
          break;
        
        case 'n': { /* store the number of written bytes in argument u32* */
          u32 *narg = va_arg(ap, u32*);
          
          if (narg != NULL) {
            *narg = off;
          } 
          
          break;
        }
        
#if PF_HANDLE_LONG == 1        
        /* 64bit number */
        case 'l': { 
          /* check if 'u' is present */
          bool ud = false;
          
          if (*(fmt + 1) == 'u' || *(fmt + 1) == 'd') {
            ud = *++fmt == 'u';
          }
          
          snprint_l(buf, len, &off, flags, width, va_arg(ap, i64), ud);
          break;
        }
#endif
/* if PF_HANDLE LONG == 1 */
        
      }
    } else {
      snprint_c(buf, len, &off, 0, 0, *fmt);
    }
  }
  
  done:
    va_end(ap);
  
  return off;
}

static void outp(char *buf, u32 cap, u32 *off, 
  pf_flags_t flags, pf_width_t width, char *str, u32 len)
{
  u32 paddw = width;
  
  if (paddw > 0 && len < paddw) {
    paddw -= len;
  }
  
  if (paddw && (flags & FLAG_LJUS)) {
    padd(buf, cap, off, flags, paddw);
    paddw = 0;
  }
  
  for (; len--; *++off) {
    if (cap > 0 && *off == cap) {
      break;
    }
    
    if (buf == NULL) {
      putchar(*str++);
    } else {
      *(buf + *off) = *str++;
    }
  }
  
  if (paddw) {
    padd(buf, cap, off, flags, paddw);
  }
}

static void padd(char *buf, u32 cap, u32 *off, 
  pf_flags_t flags, pf_width_t width)
{
  char pchr;
  
  if (flags & FLAG_PCUS) {
    pchr = (char)(flags >> 8);
  } else if (flags & FLAG_PNUL) {
    pchr = '0';
  } else {
    pchr = ' ';
  }
  
  for (; width--; ++*off) {
    if (cap > 0 && *off == cap) {
      break;
    }
    
    if (buf == NULL) {
      putchar(pchr);
    } else {
      *(buf + *off) = pchr;
    }
  }
}

static void snprint_c(char *buf, u32 cap, u32 *off, 
  pf_flags_t flags, pf_width_t width, char c)
{  
  outp(buf, cap, off, flags, width, &c, 1);
}

static void snprint_s(char *buf, u32 cap, u32 *off, 
  pf_flags_t flags, pf_width_t width, char *str)
{
  u32 len = 0;
  for (; *(str + len); ++len) ; /* no strlen() here */
  outp(buf, cap, off, flags, width, str, len);  
}

static void snprint_d(char *buf, u32 cap, u32 *off, 
  pf_flags_t flags, pf_width_t width, i32 num, char type)
{
  /* 32 bits + null-byte */
  char tmp[33] = { 0 };
  char *ptr = tmp + 33;
  u32 base = 10;
  u32 doff = 0;
  
  if (type == 'x' || type == 'X') {
    base = 16;
  } else if (type == 'o') {
    base = 8;
  } else if (type == 'b') {
    base = 2;
  }
  
  if (type == 'X') {
    doff = 36;
  }
  
  if (num < 0 && type != 'u' && type != 'x' && type != 'X' && type != 'b') {
    num = -num;
    
    /* print sign */
    snprint_c(buf, cap, off, 0, 0, '-');
    if (width > 0) --width;
    
    do {
      *--ptr = digits[num % base];
      num /= base;
    } while (num);
    
    if ((flags & FLAG_BPRX) && type == 'o') {
      /* print prefix */
      snprint_c(buf, cap, off, 0, 0, '0');
      if (width > 0) --width;
    }
  } else {
    if (type == 'd' || type == 'i' || type == 'o') {
      if (flags & FLAG_ASGN) {
        /* print sign */
        snprint_c(buf, cap, off, 0, 0, '+');
        if (width > 0) --width;
      } else if (flags & FLAG_NSGN) {
        /* print blank space instead of sign */
        snprint_c(buf, cap, off, 0, 0, ' ');
        if (width > 0) --width;
      }
    }
    
    do {
      *--ptr = digits[num % base + doff];
      num /= base;
    } while (num);
    
    if (flags & FLAG_BPRX) {
      if (type == 'X' || type == 'x' || type == 'o') {
        /* print '0' as first part of the prefix */
        snprint_c(buf, cap, off, 0, 0, '0');
        if (width > 0) --width;
      }
      
      if (type == 'X' || type == 'x' || type == 'b') {
        /* print 'x' or 'X' or 'b' as second part of the prefix */
        snprint_c(buf, cap, off, 0, 0, type);
        if (width > 0) --width;
      } 
    }
  }
  
  /* print computed string */
  snprint_s(buf, cap, off, flags, width, ptr);
}
