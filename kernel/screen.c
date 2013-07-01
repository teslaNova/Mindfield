#include <screen.h>
#include <types.h>

#include <video/bga.h>

#define TAB_WIDTH 4

static u16              video_wdh = 80 * 25 * 2;
static u16 * const  video_ptr = (u16 *) 0xB8000;

static u8 video_pos_x = 0;
static u8 video_pos_y = 0;

void k_scrn_init(void) {
  k_scrn_clear();
  
  if(bga_is_present() == true) {
    u8 bpp = bga_get_bpp_caps();
    bpp = (bpp & 32 ? 32 : bpp & 24 ? 24 : bpp & 16 ? 16 : bpp & 15 ? 15 : bpp & 8 ? 8 : 4);
    
    bga_set_bpp(bpp);
    bga_set_resolution(RES_X, RES_Y);
  }
}

void k_scrn_clear(void)
{
  for (u16 i = 0; i < video_wdh; ++i) {
    *(video_ptr + i) = 0;
  }  
  
  video_pos_x = 0;
  video_pos_y = 0;
}

void k_scrn_putc(char c)
{
  i16 pos;
  
  switch (c) {
    case '\n':
      ++video_pos_y;
      /* fallthrough */
      
    case '\r':
      video_pos_x = 0;
      return;
      
    case '\t':
      if (video_pos_x + TAB_WIDTH > 80) {
        /* goto next line */
        goto next_line;
      } else {
        /* bitop magic would be better */
        video_pos_x += (TAB_WIDTH - video_pos_x % TAB_WIDTH);
      }
      
      return;
      
    default:
      break;
  }
  
  pos = video_pos_x + video_pos_y * 80;
  *(video_ptr + pos) = (i16)(0x0F << 8 | c);
  
  if (++video_pos_x > 80) {
    next_line:
      video_pos_x = 0;
      video_pos_y += 1;
  }
}

void k_scrn_puts(char *s)
{
  for (; *s != 0; ++s) {
    k_scrn_putc(*s);
  }
}
