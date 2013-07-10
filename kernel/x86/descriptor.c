#include <descriptor.h>

#include <mm/sm.h>

segment_t segment_tbl[] = {
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

descriptor_t desc_tbl[DT_SIZE] = {
  // GDT
  {
    .limit = sizeof(segment_tbl) - 1, // read intel manual (limit-checking)
    .base_addr = (u32) segment_tbl
  },
        
  // IDT
  {0}
};
