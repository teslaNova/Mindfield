#include <cpu.h>

#include <utils.h>

#define CPUID(id) cpuid(id, &eax, &ebx, &ecx, &edx);

#define CPU_COUNT_MAX 16
#define CPUID_BS 0

static cpu_t cpu[CPU_COUNT_MAX] = {0};
static u32 cpus = 1;
#include <printf.h>
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
  CPUID(1);
  
  /* get extended information */
  /* - brand str */
  if(max_input_ext >= 0x80000004) {
    CPUID(0x80000002); // brand sting 
    memcpy(cpu[CPUID_BS].brand + 0, &eax, 4);
    memcpy(cpu[CPUID_BS].brand + 4, &ebx, 4);
    memcpy(cpu[CPUID_BS].brand + 8, &ecx, 4);
    memcpy(cpu[CPUID_BS].brand + 12, &edx, 4);
  
    CPUID(0x80000003); // brand sting 
    memcpy(cpu[CPUID_BS].brand + 16, &eax, 4);
    memcpy(cpu[CPUID_BS].brand + 20, &ebx, 4);
    memcpy(cpu[CPUID_BS].brand + 24, &ecx, 4);
    memcpy(cpu[CPUID_BS].brand + 28, &edx, 4);
  
    CPUID(0x80000004); // brand sting 
    memcpy(cpu[CPUID_BS].brand + 32, &eax, 4);
    memcpy(cpu[CPUID_BS].brand + 36, &ebx, 4);
    memcpy(cpu[CPUID_BS].brand + 40, &ecx, 4);
    memcpy(cpu[CPUID_BS].brand + 44, &edx, 4);
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
