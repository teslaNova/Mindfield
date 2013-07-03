#ifndef FONT_H_
#define FONT_H_

#include <types.h>

typedef struct {
	u8 width, height;
	u32 char_count;

	u16 *indices;
	u8 *bitmap;
} font_t;

#endif /* FONT_H_ */
