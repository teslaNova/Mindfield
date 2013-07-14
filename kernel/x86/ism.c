/* ism - x86 */
#include <ism.h>

#include <utils.h>
#include <types.h>

#include <printf.h>

ism_context *ism_handle(ism_context *r) {
  if(r->int_no >= 0 && r->int_no <= 0x20) {
    ism_handle_exception(&r);
  } else {
    ism_handle_irq(&r);
  }

  return r;
}

void ism_handle_irq(ism_context **r) {
  
}

void ism_handle_exception(ism_context **r) {
  k_printf("esp: 0x%x\n", (u32)(*r));
  k_printf("int_no: %x, error_code: %x\n", (*r)->int_no, (*r)->error_code);
  k_printf("cr0: %x, cr2: %x, cr3: %x, cr4: %x\n", (*r)->regs.cr0, (*r)->regs.cr2, (*r)->regs.cr3, (*r)->regs.cr4);
  k_printf("fs: %x, es: %x, gs: %x, ds: %x\n", (*r)->regs.fs, (*r)->regs.es, (*r)->regs.gs, (*r)->regs.ds);
  k_printf("eax: %x, ebx: %x, ecx: %x, edx: %x, edi: %x, esi: %x\n", (*r)->regs.eax, (*r)->regs.ebx, (*r)->regs.ecx, (*r)->regs.edx, (*r)->regs.edi, (*r)->regs.esi);
  
  /* (a)pic not set yet..
  if((*r)->int_no == E_TRIPPLE_FAULT) {
    for(;;);
  }
  */
}