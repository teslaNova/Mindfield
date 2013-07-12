#ifndef X86_ASM_H_
#define X86_ASM_H_

#include <types.h>

/* port actions */
void outb(u16 p, u8 d);
u8 inb(u16 p);

void outw(u16 p, u16 d);
u16 inw(u16 p);

void outl(u16 p, u32 d);
u32 inl(u16 p);

/* control register */
u32 read_cr(u8 reg);
void write_cr(u8 reg, u32 val);

/* int control */
void cli(void);
void sti(void);

/* cpu */
void hlt(void);

void cpuid(u32 id, u32 *eax, u32 *ebx, u32 *ecx, u32 *edx);

/* tsc */
u64 rdtsc(void);

#endif /* X86_ASM_H_ */
