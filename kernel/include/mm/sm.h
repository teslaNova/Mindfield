#ifndef MM_SM_H_
#define MM_SM_H_

#include <types.h>

typedef struct {
  u8 pl : 2;
  u16 limit_low : 14;
  u32 base_addr_low : 24;

  u8 accessed : 1;
  u8 rw : 1;
  u8 pbp : 1; // privileged as code or bottom_top for data (ds = 0, ss = 1)
  u8 type : 1; // 1 = code, data = 0
  
  u8 cd : 1; // code or data segment = 1, system = 0
  u8 dpl : 2;
  u8 present : 1;
  u8 limit_high : 4;
  u8 avl : 1; // available for free use.. nvm
  u8 x64 : 1;
  u8 big : 1; // 0 = 16-bit, 1 = 32-bit segment
  u8 granularity : 1; // 0 = up to 1 mbyte (bytewise), 1 = up to 4 gbyte (pagewise [4kb])
  
  u8 base_addr_high;
} __attribute__ ((packed)) segment_t;

enum {
  SMGD_CODE_RING0 = 0x8,
  SMGD_CODE_RING3 = 0x10,
  SMGD_DATA_RING0 = 0x18,
  SMGD_DATA_RING3 = 0x20
};

void sm_setup(void);

#endif /* MM_SM_H_ */
