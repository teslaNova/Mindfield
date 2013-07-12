#ifndef CPU_H_
#define CPU_H_

#include <types.h>

typedef struct {
  // basic info
  char brand[49];
  u8 init_apic_id;
  
  u8 sse;
  u8 mmx : 1;
  
  u8 apic : 1;
  u8 x2apic : 1;
  
  u8 fpu : 1;
  
  u8 pse : 1; // page size extension (4mb pages)
  u8 pae : 1; // physical address extension (phys. addr > 32-bit)
  
  u8 tsc : 1; // timestamp counter (instruction: rdtsc)
  
  u8 msr; // model specific registers (instruction: rdmsr, wrmsr)
} __attribute__ ((packed)) cpu_t;

void cpu_detect(void);

u32 cpu_count(void);

const cpu_t *cpu_get(u32 n);
const cpu_t *cpu_get_bs(void);

#endif /* CPU_H_ */
