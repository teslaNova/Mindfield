#include <mm/sm.h>

#ifdef ARCH_X86
#include <x86/descriptor.h>
#endif

#include <printf.h>

/*
  notes:
    we always assume to boot via grub, so cr0.pe will always be true
*/
void sm_setup(void) {
  __asm__ volatile (
    "lgdt %0; hlt;"
    "ljmp %1, $rel;"
    "rel:;"
    " mov %%ax, %%ds;"
    " mov %%ax, %%es;"
    " mov %%ax, %%fs;"
    " mov %%ax, %%ss;"
    " mov %%ax, %%gs;"
      :: "m"(desc_tbl[DTI_GDT]), "i"(SMGD_CODE_RING0), "a"(SMGD_DATA_RING0)
  );
}
