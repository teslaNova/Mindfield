#include <video/bga.h>

#include <screen.h>

#include <pci.h>
#include <utils.h>

#include <font.h>

#ifndef RES_X
#define RES_X 800
#endif

#ifndef RES_Y
#define RES_Y 600
#endif

#define BGA_VENDOR 0x1234
#define BGA_DEVICE 0x1111

#define BGA_P_REGSEL 0x01CE
#define BGA_P_REGDAT 0x01CF

enum {
  BGAC_RES = 1,
  BGAC_8BPP_ONLY = 2,
  BGAC_XY_OFF = 4,
  BGAC_32BPP = 8,
  BGAC_FRM_BUFFER = 16,
  BGAC_BUILTIN_CAPS = 32,
};

enum bga_register {
  BGAR_ID = 0,
  BGAR_XRES,
  BGAR_YRES,
  BGAR_BPP,
  BGAR_ENABLE,
  BGAR_BANK,
  BGAR_VWIDTH,
  BGAR_VHEIGHT,
  BGAR_XOFF,
  BGAR_YOFF,
};

enum {
  BGA_EF_DISABLE = 0,
  BGA_EF_ENABLE = 1,
  BGA_EF_LFR = 0x40,
  BGA_EF_NOT_CLEAR = 0x80
};

static u8 bga_capabilities = 0;

static u32 *bga_video_ptr = (u32 *) 0xA0000;
static u32 bga_video_pos_x = 0;
static u32 bga_video_pos_y = 0;
static u32 bga_video_res_x = RES_X;
static u32 bga_video_res_y = RES_Y;

static u32 bga_font_color_fg = 0xFFFFFFFF;
static u32 bga_font_color_bg = 0;

extern const font_t font;

static u16 bga_read(enum bga_register reg) {
  outw(BGA_P_REGSEL, reg);
  return inw(BGA_P_REGDAT);
}

static void bga_write(enum bga_register reg, u16 data) {
  outw(BGA_P_REGSEL, reg);
  outw(BGA_P_REGDAT, data);
}

static void bga_set_state(bool enable) {
  bga_write(BGAR_ENABLE, enable | BGA_EF_NOT_CLEAR | BGA_EF_LFR);
}

bool bga_is_present(void) {
  switch(bga_read(BGAR_ID)) {
    case 0xB0C0: bga_capabilities |= BGAC_RES; bga_capabilities |= BGAC_8BPP_ONLY;
    case 0xB0C1: bga_capabilities &= ~BGAC_8BPP_ONLY; bga_capabilities |= BGAC_XY_OFF;
    case 0xB0C2: bga_capabilities |= BGAC_32BPP; bga_capabilities |= BGAC_FRM_BUFFER;
    case 0xB0C3: bga_capabilities |= BGAC_BUILTIN_CAPS;
    case 0xB0C4:
    case 0xB0C5: break;
    default: return false;
  }
  
  return true;
}

bool bga_init(void) {
  u8 bpp = bga_get_bpp_caps();
  bpp = (bpp & 32 ? 32 : bpp & 24 ? 24 : bpp & 16 ? 16 : bpp & 15 ? 15 : bpp & 8 ? 8 : 4);

  if(bga_set_bpp(bpp) == false) {
    return false;
  }
  
  if(bga_set_resolution(bga_video_res_x, bga_video_res_y) == false) {
    return false;
  }
  
  const pci_entry_t *bga_dev = pci_get_device(BGA_VENDOR, BGA_DEVICE);

  if(bga_dev != NULL) { // LINEAR FRAMEBUFFER TAKE ME!
    bga_video_ptr = (u32 *) (bga_dev->data.type0.bar0.raw & 0xFFFFFFF0);
  } else {
    return false; // banked mode not supported
  }
  
  return true;
}

bool bga_set_resolution(u16 x, u16 y) {
  if(x % 8 != 0) { // qemu restriction (see: wiki.osdev.org/Bochs_VBE_Extensions - Setting display resolution and bit depth)
    return false;
  }
  
  bga_set_state(false);
  bga_write(BGAR_XRES, x);
  bga_write(BGAR_YRES, y);
  bga_set_state(true);
  
  return true;
}

u16 bga_get_x_resolution(void) {
  return bga_read(BGAR_XRES);
}

u16 bga_get_y_resolution(void) {
  return bga_read(BGAR_YRES);
}

bool bga_set_bpp(u8 bpp) {
  if(bga_capabilities & BGAC_8BPP_ONLY) {
    const u8 bm = 8 | 4;
    bpp &= bm;
    bpp = (bpp == bm ? 0 : bpp);
  }
  
  if(bga_capabilities & BGAC_32BPP) {
    const u8 bm = 32 | 24 | 16 | 15 | 8 | 4;
    bpp &= bm;
    bpp = (bpp == bm ? 0 : bpp);
  }
  
  if(bpp != 0) {
    bga_set_state(false);
    bga_write(BGAR_BPP, bpp);
    bga_set_state(true);
    
    return true;
  }
  
  return false;
}

u8 bga_get_bpp(void) {
  return (u8) bga_read(BGAR_BPP);
}

u8 bga_get_bpp_caps(void) {
  if(bga_capabilities & BGAC_8BPP_ONLY) {
    return 0b1100;
  }
  
  if(bga_capabilities & BGAC_32BPP) {
    return 0b00111101;
  }
  
  return 0;
}

void bga_set_x_offset(u16 x) {
  bga_write(BGAR_XOFF, x);
}

u16 bga_get_x_offset(void) {
  bga_read(BGAR_XOFF);
}

void bga_set_y_offset(u16 y) {
  bga_write(BGAR_YOFF, y);
}

u16 bga_get_y_offset(void) {
  bga_read(BGAR_YOFF);
}

void bga_set_bank(u16 bank) {
  bga_write(BGAR_BANK, bank);
}

void bga_clear(void) {
  bga_write(BGAR_ENABLE, BGA_EF_DISABLE | BGA_EF_LFR);
  bga_write(BGAR_ENABLE, BGA_EF_ENABLE | BGA_EF_LFR);
}

void inline bga_draw(u32 x, u32 y, u32 rgb) {
  bga_video_ptr[x + y] = rgb;
}

void bga_putc(char c) { 
  u16 fi = 0;
  
  switch(c) {
    case '\n': {
      bga_video_pos_y += bga_video_res_x * font.height;
    };
    
    case '\r': {
      bga_video_pos_x = 0;
    } return;
    
    case '\t': {
      bga_video_pos_x += TAB_WIDTH;
    } return;
    
    default: {
      for(fi=0;fi<font.char_count;fi++) { // locate char
        if(font.indices[fi] == c) break;
      }
  
      if(fi == font.char_count) {
        return;
      }
    }
  }
  
  if(bga_video_pos_x >= bga_video_res_x) {
    bga_video_pos_x = 0;
    bga_video_pos_y += bga_video_res_x * font.height;
  }
  
  for(u32 j=0; j<font.height; j++) {
    for(u32 k=0; k<font.width; k++) {
      if(font.bitmap[fi * font.height + j] & (1 << k)) {
        bga_draw((font.width - k) + bga_video_pos_x, bga_video_res_x * j + bga_video_pos_y, bga_font_color_fg);
      } else {
        bga_draw((font.width - k) + bga_video_pos_x, bga_video_res_x * j + bga_video_pos_y, bga_font_color_bg);
      }
    }
  }
    
  bga_video_pos_x += font.width + 1;
}
