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

typedef unsigned long paddr_t;
typedef unsigned long vaddr_t;

#define true 1
#define false 0
#define bool _Bool

#undef size_t
#if defined(ARCH_X86)
#define size_t u32
#elif defined(ARCH_X64)
#define size_t u64
#endif

typedef struct {
  u32 cr4, cr3, cr2, cr0;
  u32 ds, es, fs, gs;
  
#ifdef ARCH_X86
  u32 edi, esi, ebp, old_esp, ebx, edx, ecx, eax;
#elif ARCH_X64
  u64 rdi, rsi, rbp, old_rsp, rbx, rdx, rcx, rax;
#endif
  
} regs_t;

#endif /* TYPES_H_ */
