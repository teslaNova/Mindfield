#ifndef ISM_H_
#define ISM_H_

#include <types.h>

typedef struct {
  u16 offset_low;
  u16 segment_selector;
  
  u8 _res0 : 5;
  u8 _zero : 3;

  u8 type : 3;
  u8 big : 1; // 16-bit = 0, 32-bit = 1
  u8 dpl : 2;
  u8 present : 1;
  
  u16 offset_high;
} __attribute__ ((packed)) gate_t;

enum {
  ISG_TYPE_TASK = 0b101,
  ISG_TYPE_INT = 0b110,
  ISG_TYPE_TRAP = 0b111
};

void ism_setup(void);

#endif /* ISM_H_ */
