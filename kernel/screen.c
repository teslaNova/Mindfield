#include <screen.h>

#include <video/tm.h>
#include <video/bga.h>

void (*k_scrn_clear)(void) = tm_clear;
void (*k_scrn_putc)(char) = tm_putc;

void k_scrn_init(void) {
  tm_init();
  
/*  if(bga_is_present() == true && bga_init() == true) {
    k_scrn_clear = bga_clear;
    k_scrn_putc = bga_font_putc;
  }
  */
  k_scrn_clear();
}

void k_scrn_puts(char *s)
{
  for (; *s != 0; ++s) {
    k_scrn_putc(*s);
  }
}
