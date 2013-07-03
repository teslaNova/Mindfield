#include <multiboot.h> // multiboot_...
#include <types.h> // iN, uN

#include <screen.h>
#include <video/bga.h>

#include <printf.h>

#include <mm/pmm.h>
#include <mm/malloc.h>

#include <rtc.h>

#include <utils.h>

#include <pci.h>

void panic(void) {
  k_printf("panic() called. halting.");
  
  __asm__ volatile ("hlt");
  for(;;);
}

void k_main(multiboot_info_t *mb_info, u32 mb_magic) {
  pci_scan();
  
  k_scrn_init();
  
  k_printf("Mindfield\n");
  
  if(mb_magic != MULTIBOOT_BOOTLOADER_MAGIC) {
    k_printf("System Halted.\n");
    panic();
  }
  
  k_printf("- Initializing PMM\n\n");
  pmm_setup(mb_info->mmap_addr, mb_info->mmap_length);
  
  for(rtc_datetime_t dt={0};;rtc_get_datetime(&dt)) {
    k_printf("\rIt is %d.%d.%d %d:%d:%d", dt.day, dt.month, dt.year, dt.hours, dt.minutes, dt.seconds);
    rtc_sleep(1);
  }
}