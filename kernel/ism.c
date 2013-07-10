#include <ism.h>

#ifdef ARCH_X86
#include <x86/descriptor.h>
#include <x86/gates.inl>
#endif

#include <utils.h>

#include <types.h>

static u32 int_gate_start = 0;
static u32 int_gate_size = 0;

void ism_setup(void) {
  /* retrieve gate size and offset of the first gate. then update gate descriptors */
  __asm__ (
    "mov $_int_gate1, %%eax;"
    "mov $_int_gate0, %%ebx;"
    "subl %%ebx, %%eax;"
    "mov $_int_gate0, %%ecx"
      : "=a" (int_gate_size), "=c" (int_gate_start)
  );
  
  gate_t *gate = (gate_t *) (desc_tbl[DTI_IDT].base_addr);
  
  for(u32 i=0; i<DT_I_SIZE; i++, gate++) {
    gate->offset_low = (u16) (int_gate_start + int_gate_size * i);
    gate->offset_high = (u16) (int_gate_start + int_gate_size * i)  >> 16;
  } 
  
  __asm__ volatile (
    "lidt %0"
      :: "m"(desc_tbl[DTI_IDT])
  );
}