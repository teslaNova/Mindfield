#ifndef ITOA_H_
#define ITOA_H_

#include <types.h>

char *itoa(i32, char*, u32);
char *ltoa(i64, char*, u32);

/* uses a extra buffer */
void itoa_b(i32, char*, u32);
void ltoa_b(i64, char*, u32);

#endif
