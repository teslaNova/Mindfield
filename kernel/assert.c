#include <assert.h>
#include <printf.h>

#ifndef NDEBUG

void assert_fail(const char *expr, 
  const char *file, u32 line, const char *func)
{
  k_printf("%s:%u (%s) Assertion '%s' failed.",
    file, line, func, expr);
  
  panic();
  
  /* no return */
  for(;;) ;
}

#endif
