#ifndef VIDEO_BGA_H_
#define VIDEO_BGA_H_

#include <types.h>

bool bga_is_present(void);

bool bga_set_resolution(u16 x, u16 y);
u16 bga_get_x_resolution(void);
u16 bga_get_y_resolution(void);

bool bga_set_bpp(u8 bpp);
u8 bga_get_bpp(void);
u8 bga_get_bpp_caps(void);

#endif /* VIDEO_BGA_H_ */
