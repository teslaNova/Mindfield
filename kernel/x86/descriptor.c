#include <descriptor.h>

#include <mm/sm.h>
#include <ism.h>

#define GATE(sel, _32bit, _type, _dpl) {.segment_selector=sel, ._zero=0, .type=_type, .big=_32bit, .dpl=_dpl, .present=1}
#define INT_GATE(sel, _32bit, _dpl) GATE(sel, _32bit, ISG_TYPE_INT, _dpl)
#define INT_GATE_32BIT(sel, _dpl) INT_GATE(sel, true, _dpl)
#define INT_GATE_32BIT_RING0() INT_GATE_32BIT(SMGD_CODE_RING0, 0)

segment_t segment_tbl[DT_G_SIZE] = {
  // null desc
  {0},
  
  // cs ring 0
  {
    .pl = 0, 
    .limit_low = 0x3FFF,
    .base_addr_low = 0,
    .accessed = 1, .rw = 1, .pbp = 1, .type = 1,
    .cd = 1,
    .dpl = 0,
    .present = 1,
    .limit_high = 0xF,
    .avl = 1,
    .x64 = 0,
    .big = 1,
    .granularity = 1,
    .base_addr_high = 0
  },
  
  // cs ring 3
  {
    .pl = 3, 
    .limit_low = 0x3FFF,
    .base_addr_low = 0,
    .accessed = 1, .rw = 1, .pbp = 1, .type = 1,
    .cd = 1,
    .dpl = 3,
    .present = 1,
    .limit_high = 0xF,
    .avl = 1,
    .x64 = 0,
    .big = 1,
    .granularity = 1,
    .base_addr_high = 0
  },
  
  // ds ring 0
  {
    .pl = 0, 
    .limit_low = 0x3FFF,
    .base_addr_low = 0,
    .accessed = 1, .rw = 1, .pbp = 0, .type = 0,
    .cd = 1,
    .dpl = 0,
    .present = 1,
    .limit_high = 0xF,
    .avl = 1,
    .x64 = 0,
    .big = 1,
    .granularity = 1,
    .base_addr_high = 0
  },
  
  // ds ring 3
  {
    .pl = 3, 
    .limit_low = 0x3FFF,
    .base_addr_low = 0,
    .accessed = 1, .rw = 1, .pbp = 0, .type = 0,
    .cd = 1,
    .dpl = 3,
    .present = 1,
    .limit_high = 0xF,
    .avl = 1,
    .x64 = 0,
    .big = 1,
    .granularity = 1,
    .base_addr_high = 0
  }
};

gate_t gate_tbl[DT_I_SIZE] = {
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0(),
  INT_GATE_32BIT_RING0()
};

descriptor_t desc_tbl[DT_SIZE] = {
  // GDT
  {
    .limit = sizeof(segment_t) * DT_G_SIZE  - 1, // read intel manual (limit-checking)
    .base_addr = (u32) segment_tbl
  },
        
  // IDT
  {
    .limit = sizeof(gate_t) * DT_I_SIZE  - 1, // read intel manual (limit-checking)
    .base_addr = (u32) gate_tbl
  }
};
