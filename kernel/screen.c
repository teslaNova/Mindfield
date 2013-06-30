#include <screen.h>
#include <types.h>

#define TAB_WIDTH 4

static const u16   video_wdh = 80 * 25 * 2;
static u16 * const video_ptr = (u16 *) 0xB8000;

u8 video_pos_x = 0;
u8 video_pos_y = 0;

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
