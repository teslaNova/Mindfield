#include <multiboot.h> // multiboot_...
#include <types.h> // iN, uN

#include <screen.h>
#include <printf.h>

#include <mm/sm.h>
#include <mm/pmm.h>
//#include <mm/vmm.h>

//#include <cpu.h>
//#include <ism.h>
//#include <sched.h>
//#include <module.h>

#include <rtc.h>

#include <pci.h>

#include <utils.h>

void panic(void) {
  k_printf("panic() called. halting.");
  
  hlt();
  for(;;);
}

void k_main(multiboot_info_t *mb_info, u32 mb_magic) {
  pci_scan();
  
  k_scrn_init();
  
  k_printf("Mindfield\n\n");
  
  k_printf("Gathering System Information..\n");
  k_printf("Found %d PCI Devices\n\n", pci_count());
//  cpu_detect();
  
  if(mb_magic != MULTIBOOT_BOOTLOADER_MAGIC) {
    k_printf("System Halted.\n");
    panic();
  }
  
  k_printf(" - initializing SM\n");
  sm_setup(); // segmentation manager
  
  k_printf(" - Initializing PMM\n");
  pmm_setup(mb_info->mmap_addr, mb_info->mmap_length / sizeof(memory_map_t));
  
  k_printf(" - initializing VMM\n");
//  vmm_setup();
  
  k_printf(" - initializing ISM\n");
//  ism_setup(); // interrupt service manager (ints & exceptions)
  
  k_printf(" - initializing Scheduler\n");
//  sched_setup();
  
  k_printf(" - Loading Modules..\n");
  
  module_t *mod = (module_t *) mb_info->mods_addr;
  for(u32 i=0; i<mb_info->mods_count; i++, mod++) {
  //    mod_load(mod);
  }
  
  for(rtc_datetime_t dt={0};;rtc_get_datetime(&dt)) {
    k_printf("\rIt is %02d.%02d.%2d %02d:%02d:%02d", dt.day, dt.month, dt.year, dt.hours, dt.minutes, dt.seconds);
    rtc_sleep(1);
  }
}