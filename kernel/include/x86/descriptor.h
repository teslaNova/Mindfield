#ifndef X86_DESCRIPTOR_H_
#define X86_DESCRIPTOR_H_

#include <types.h>

typedef struct {
  u16 limit;
  u32 base_addr;
} __attribute__((packed)) descriptor_t;

#define DT_SIZE 2
#define DT_G_SIZE 5
#define DT_I_SIZE 256

enum {
  DTI_GDT = 0,
  DTI_IDT,
};

extern descriptor_t desc_tbl[DT_SIZE];

//void desc_update(void);

#endif /* X86_DESCRIPTOR_H_ */
