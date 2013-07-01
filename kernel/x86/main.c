#include <multiboot.h> // multiboot_...
#include <types.h> // iN, uN

#include <screen.h>
#include <printf.h>

#include <mm/pmm.h>
#include <mm/malloc.h>

#include <rtc.h>

#include <utils.h>

void panic(void) {
  __asm__ volatile ("hlt");
  for(;;);
}

void k_main(multiboot_info_t *mb_info, u32 mb_magic) {
  k_cls();
  k_printf("Mindfield\n");
  
  if(mb_magic != MULTIBOOT_BOOTLOADER_MAGIC) {
    k_printf("System Halted.\n");
    panic();
  }
  
  k_printf("- Initializing PMM\n\n");
  pmm_setup(mb_info->mmap_addr, mb_info->mmap_length);
  
  for(rtc_datetime_t dt={.year=-1};;rtc_get_datetime(&dt)) {
    if(dt.year != (u16)-1) {
      k_printf("It is %d.%d.%d %d:%d:%d.\r", dt.day, dt.month, dt.year, dt.hours, dt.minutes, dt.seconds);
    }
    rtc_sleep(1);
  }
}