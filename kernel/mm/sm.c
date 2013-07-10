#include <mm/sm.h>

#ifdef ARCH_X86
#include <x86/descriptor.h>
#endif

#include <utils.h>

//#include <printf.h>

extern void panic();

void sm_setup(void) {
  if(read_cr(0) & 1 == 0) { // we always assume to boot via grub, so cr0.pe will always be true
    panic();
  }
  
  /*extern segment_t segment_tbl[];
  for(u32 i=1; i<5; i+=2) {
    k_printf("limit: %08x\nbase addr: 0x0%08x\n\n",
      segment_tbl[i].limit_low << 2 | segment_tbl[i].limit_high << 16,
      segment_tbl[i].base_addr_low | segment_tbl[i].base_addr_high << 24
    );
  }*/
  
  __asm__ volatile (
    "lgdt %0; "
    "ljmp %1, $rel;"
    "rel:"
    " mov %%ax, %%ds;"
    " mov %%ax, %%es;"
    " mov %%ax, %%fs;"
    " mov %%ax, %%ss;"
    " mov %%ax, %%gs;"
      :: "m"(desc_tbl[DTI_GDT]), "i"(SMGD_CODE_RING0), "a"(SMGD_DATA_RING0)
  );
}
