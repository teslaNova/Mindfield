#include <multiboot.h> // multiboot_...
#include <types.h> // iN, uN

#include <mm/pmm.h>

void k_main(multiboot_info_t *mb_info, u32 mb_magic) {
  if(mb_magic != MULTIBOOT_BOOTLOADER_MAGIC) {
    // k_printf HAALP
    for(;;);
  }
  
  pmm_setup(mb_info->mmap_addr, mb_info->mmap_length);
  
  for(;;);
}