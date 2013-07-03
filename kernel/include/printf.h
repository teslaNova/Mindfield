#ifndef PRINTF_H_
#define PRINTF_H_

#include <types.h>

#define k_printf(args...) (void) k_snprintf(NULL, 0, args)
#define k_sprintf(buf, fmt, args...) k_snprintf(buf, 0, fmt, args)

u32 k_snprintf(char*, u32, const char*, ...);

#endif
