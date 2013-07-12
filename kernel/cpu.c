#include <cpu.h>

#include <utils.h>

#define CPUID(id) cpuid(id, &eax, &ebx, &ecx, &edx);

#define CPU_COUNT_MAX 16
#define CPUID_BS 0

#define CHFLG(r, b, m) (cpu[CPUID_BS].m = (r & (1 << b)) ? true : false);

static cpu_t cpu[CPU_COUNT_MAX] = {0};
static u32 cpus = 1;

void cpu_detect(void) {
  u32 eax, ebx, ecx, edx;
  u32 max_input_basic = 0, max_input_ext = 0;
  
  /* checking basic & extended max input val and vendor */
  CPUID(0);
  max_input_basic = eax;
  
  /* vendor check */
  if(ebx != *(u32 *)"Genu" || ecx != *(u32 *)"ntel" || edx != *(u32 *)"ineI") {
    goto _amd;
  }
  
  CPUID(0x80000000);
  max_input_ext = eax;

_intel:  
  /* basic information */
  CPUID(1);
  
  cpu[CPUID_BS].init_apic_id = (u8)(ebx >> 24);
  
  if(ecx & (1 << 20)) {
    cpu[CPUID_BS].sse = 42;
  } else if (ecx & (1 << 19)) {
    cpu[CPUID_BS].sse = 41;
  } else if (ecx & (1 << 0)) {
    cpu[CPUID_BS].sse = 30;
  } else if(edx & (1 << 26)) {
    cpu[CPUID_BS].sse = 20;
  } else if (edx & (1 << 25)) {
    cpu[CPUID_BS].sse = 10;
  }

  CHFLG(edx, 9, apic);
  CHFLG(ecx, 21, x2apic);
  CHFLG(edx, 0, fpu);
  CHFLG(edx, 3, pse);
  CHFLG(edx, 4, tsc);
  CHFLG(edx, 5, msr);
  CHFLG(edx, 6, pae);
  CHFLG(edx, 23, mmx);
  
  /* extended information */
  /* - brand str */
  if(max_input_ext >= 0x80000004) {
    for(u32 i=0; i<3; i++) {
      CPUID(0x80000002 + i); // brand sting 
      memcpy(cpu[CPUID_BS].brand + (i * 16 + 0), &eax, 4);
      memcpy(cpu[CPUID_BS].brand + (i * 16 + 4), &ebx, 4);
      memcpy(cpu[CPUID_BS].brand + (i * 16 + 8), &ecx, 4);
      memcpy(cpu[CPUID_BS].brand + (i * 16 + 12), &edx, 4);
    }
  }
  
  return;
  
_amd:
  /* vendor check */
  if(ebx != *(u32 *)"Genu" || ecx != *(u32 *)"ntel" || edx != *(u32 *)"ineI") { // incorrect: check vals in amd docs
    goto _misc;
  }
  
_misc:
  return;
}

u32 cpu_count(void) {
  return cpus;
}

const cpu_t *cpu_get(u32 n) {
  if(n > cpus-1) {
    return NULL;
  }
  
  return (const cpu_t *) &cpu[n];
}

inline const cpu_t * cpu_get_bs(void) { // bootstrap cpu
  return (const cpu_t *) &cpu[CPUID_BS];
}
