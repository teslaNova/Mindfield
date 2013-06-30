#include <multiboot.h> // multiboot_...
#include <types.h> // iN, uN

#include <screen.h>
#include <printf.h>

#include <mm/pmm.h>

void k_main(multiboot_info_t *mb_info, u32 mb_magic) {
  k_cls();
  
  k_printf("Mindfield.\n");
  
  if(mb_magic != MULTIBOOT_BOOTLOADER_MAGIC) {
    k_printf("System Halted.\n");
    for(;;);
  }
  
  k_printf("- Initializing PMM\n");
  pmm_setup(mb_info->mmap_addr, mb_info->mmap_length);
  
  for(;;);
}