#ifndef TYPES_H_
#define TYPES_H_

#define NULL (void *)0

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long int u64;

typedef char i8;
typedef short i16;
typedef int i32;
typedef long long int i64;

typedef u32 paddr_t;
typedef u32 vaddr_t;

#define true 1
#define false 0
#define bool _Bool

#undef size_t
#define size_t u32

#endif /* TYPES_H_ */
