#ifndef DESCRIPTOR_H_
#define DESCRIPTOR_H_

#include <types.h>

typedef struct {
  u16 limit;
  u32 base_addr;
} __attribute__((packed)) descriptor_t;

#define DT_SIZE 2

enum {
  DTI_GDT = 0,
  DTI_IDT,
};

extern descriptor_t desc_tbl[DT_SIZE];

#endif /* DESCRIPTOR_H_ */
