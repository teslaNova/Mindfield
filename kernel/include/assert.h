#ifndef ASSERT_H_
#define ASSERT_H_

#ifndef NDEBUG
#include <types.h>

void assert_fail(const char*, const char*, u32, const char*)
  __attribute__ ((__noreturn__));

#undef assert
#define assert(expr) \
  ((expr) ? (void) 0 : assert_fail(""#expr"", __FILE__, __LINE__, __func__)) 

#else
/* NDEBUG */

#define assert(expr) (void) 0

#endif
  
#endif
