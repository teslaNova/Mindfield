#include <screen.h>
#include <video/tm.h>

static u16    video_res_x = 80;
static u16    video_res_y = 25;
static u16    video_wdh = 0;
static u16*   video_ptr = (u16 *) 0xB8000;

static u16    video_pos_x = 0;
static u16    video_pos_y = 0;

void tm_init(void) {
  video_wdh = (video_res_x * video_res_y * 2);
}

void tm_clear(void) {
  for (u16 i = 0; i < video_wdh; ++i) {
    *(video_ptr + i) = 0;
  }  
  
  video_pos_x = 0;
  video_pos_y = 0;
}

void tm_putc(char c)
{
  switch (c) {
    case '\n':
      ++video_pos_y;
      /* fallthrough */
      
    case '\r':
      video_pos_x = 0;
      return;
      
    case '\t':
      if (video_pos_x + TAB_WIDTH > video_res_x) {
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
  
  i16 pos = video_pos_x + video_pos_y * video_res_x;
  *(video_ptr + pos) = (i16)(0x0F << 8 | c);
  
  if (++video_pos_x > video_res_x) {
    next_line:
      video_pos_x = 0;
      video_pos_y += 1;
  }
}
