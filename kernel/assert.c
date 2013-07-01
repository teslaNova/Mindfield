#include <assert.h>
#include <printf.h>

#ifndef NDEBUG

extern void panic(void);

void assert_fail(const char *expr, 
  const char *file, u32 line, const char *func)
{
  k_printf("%s:%u (%s) Assertion '%s' failed.",
    file, line, func, expr);
  
  panic();
  for(;;);
}

#endif
