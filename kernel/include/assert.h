#ifndef ASSERT_H_
#define ASSERT_H_

#ifndef NDEBUG

#include <screen.h>
#include <print.h>

#define assert(expr)                                        \
  if (!(expr)) {                                            \
    k_puts("assertion failed: #expr", __FILE__, __LINE__);  \
    panic();                                                \
  }

#else

#define assert(expr)

#endif

#endif
