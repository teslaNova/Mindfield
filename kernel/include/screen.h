#ifndef SCREEN_H_
#define SCREEN_H_

#include <types.h>

void k_scrn_cls(void);
void k_scrn_putc(char);
void k_scrn_puts(char*);

/* i like stuff namespaced, but those two functions
   gonna be heavly used in the kernel. */
   
#define k_putc k_scrn_putc
#define k_puts k_scrn_puts

#endif
