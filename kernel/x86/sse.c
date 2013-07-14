#include <sse.h> // at least sse 2.0
#include <asm.h>

inline void sse_init(void) {
  write_cr(4, read_cr(4) | (1 << 9)); // Intel System Programming Guide - V3 9.6 
}

inline void *sse_memcpy(void *dest, const void *src, u32 n) {
  __asm__ volatile (
    ".cpdq:"
      "movdqu (%%esi), %%xmm0;"
      "movdqu %%xmm0, (%%edi);"
      "add $16, %%esi;"
      "add $16, %%edi;"
      "sub $16, %%ecx;"
      "jz .cpdn;"
      "cmp $16, %%ecx;"
      "jl .cpb;"
      "jmp .cpdq;"
    ".cpb:"
      "cld;lodsb;stosb;"
      "dec %%ecx;"
      "jne .cpb;"
    ".cpdn:;"
    :: "D"(dest), "S"(src), "c" (n)
  );
  
  return dest;
}

inline int sse_memcmp(void *l1, void *l2, u32 len) {
  register int *eax __asm__ ("eax");
  
  __asm__ volatile (
    "xor %%eax, %%eax;"
    ".cmpdq:"
      "movdqu (%%esi), %%xmm0;"
      "movdqu (%%edi), %%xmm2;"
      "movdqu (%%edi), %%xmm3;"  
      "pcmpeqb %%xmm0, %%xmm2;" // l2 == l1 
      "pcmpgtb %%xmm0, %%xmm3;" // l2 < l1
        "pmovmskb %%xmm2, %%ebx;"
        "pmovmskb %%xmm3, %%edx;"
        "cmp $0xFFFF, %%bx;" // l2 == l1 
        "je .cmpdq_c;"
        "cmp $0, %%dx;" // l2 > l1
        "je .cmp_gt;" // true, l2 > l1
        "mov $-1, %%eax;" // false, l1 > l2
        "jmp .cmpdn;"
        ".cmp_gt:"
        "mov $1, %%al;"
        "jmp .cmpdn;"
    ".cmpdq_c:"
      "add $16, %%esi;"
      "add $16, %%edi;"
      "sub $16, %%ecx;"
      "jz .cmpdn;"
      "cmp $16, %%ecx;"
      "jl .cmpb;"
      "jmp .cmpdq;"
    ".cmpb:"
      "cmpsb (%%esi), (%%edi);"
      "je .cmpb_c;"
      "jl .cmpb_lt;"
      "mov $-1, %%eax;"
      "jmp .cmpdn;"
      ".cmpb_lt:"
      "mov $1, %%al;"
      "jmp .cmpdn;"
      ".cmpb_c:"
      "dec %%esi;"
      "dec %%edi;"
      "dec %%ecx;"
      "jne .cpb;"
    ".cmpdn:;"
    :: "D"(l1), "S"(l2), "c" (len) : "memory"
  );
  
  return (int)eax;
}

inline const void *sse_memchr(const void *t, u32 v, u32 n) {
  register void *esi __asm__ ("esi") = (void *) t;
  
  __asm__ volatile (
    ""
    :: "m"(v), "c"(n)
  );
  
  return esi;
}

inline void *sse_memset(void *dest, u32 v, u32 n) {
  v &= 0xFF;
  v = v | (v << 8) | (v << 16) | (v << 24);
  u32 v128[4] = {v,v,v,v};

  __asm__ volatile (  
    "movdqu %[val], %%xmm0;"
    ".msdq:;"
      "movdqu %%xmm0, (%%edi);"
      "add $16, %%edi;"
      "sub $16, %%ecx;"
      "jz .msdn;"
      "cmp $16, %%ecx;"
      "jl .msb;"
      "jmp .msdq;"
    ".msb:"
      "movb %[val], %%al;"
      "cld;"
      "rep stosb;"
    ".msdn:;"
    :: "D"(dest), "c"(n), [val] "m"(v128)
  );
  
  return dest;
}
