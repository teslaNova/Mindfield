#include <video/bga.h>

#include <utils.h>

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

u8 bga_capabilities = 0;

enum bga_register {
  BGAR_ID = 0,
  BGAR_XRES,
  BGAR_YRES,
  BGAR_BPP,
  BGAR_ENABLE,
  BGAR_BANK,
  BGAR_VWITH,
  BGAR_VHEIGHT,
  BGAR_XOFF,
  BGAR_YOFF,
};

static u16 bga_read(enum bga_register reg) {
  outw(BGA_P_REGSEL, reg);
  return inw(BGA_P_REGDAT);
}

static void bga_write(enum bga_register reg, u16 data) {
  outw(BGA_P_REGSEL, reg);
  outw(BGA_P_REGDAT, data);
}

static void bga_set_state(bool enable) {
  bga_write(BGAR_ENABLE, enable);
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
  
}

u16 bga_get_y_resolution(void) {
  
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