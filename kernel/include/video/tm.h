#ifndef VIDEO_TM_H_ // textmode
#define VIDEO_TM_H_

#include <types.h>

void tm_init(void);

void tm_clear(void);
void tm_putc(char c);

#endif /* VIDEO_TM_H_ */
