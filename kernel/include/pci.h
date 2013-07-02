#ifndef PCI_H_
#define PCI_H_

#include <types.h>

typedef struct {
  union {
    struct {
      u8 null : 1;
      u8 type : 2;
      u8 prefetchable : 1;
      
      u32 base_addr : 28;
    } mem;
    
    struct {
      u8 null : 1;
      u8 _res0 : 1;
      u32 base_addr : 30;
    } io;
    
    u32 raw;
  };
} bar_t;

typedef enum {
  CLC_DEV_DEPR = 0,
  CLC_MASS_STORAGE_CTRL,
  CLC_NETWORK_CTRL,
  CLC_DISPLAY_CTRL,
  CLC_MULTIMEDIA_CTRL,
  CLC_MEMORY_CTRL,
  CLC_BRIDGE_DEV,
  CLC_COMM_CTRLS,
  CLC_BASE_SYS_PERIPH,
  CLC_INPUT_DEV,
  CLC_DOCKING_STATIONS,
  CLC_PROCESSORS,
  CLC_SERIAL_BUS_CTRL,
  CLC_WIRELESS_CTRL,
  CLC_INTELLIGENT_IO_CTRL,
  CLC_SATELLITE_COMM_CTRL,
  CLC_CRYPT_CTRL,
  CLC_DATA_PROCESSING_CTRL,
  CLC_RESERVED,
  CLC_UNKNOWN = 0xFF
} class_code_t;

typedef struct {
  struct {
    u16 vendor_id;
    u16 device_id;

    union {
      struct {
        u8 io_space : 1;
        u8 mem_space : 1;
        u8 bus_master : 1;
        u8 special_cycles : 1;
        u8 mem_write_inv_enable : 1;
        u8 vga_palette : 1;
        u8 par : 1; // parity error response
        u8 _res0 : 1;
        u8 serr_num_enable : 1;
        u8 fast_btb_enable : 1; // back to black
        u8 int_disable : 1;
        u8 _res1 : 4;
      } data;
      
      u16 raw;
    } command;
    
    union {
      struct {
        u8 _res0 : 3;
        u8 int_status : 1;
        u8 capabilities_list : 1;
        u8 capable_66mhz : 1;
        u8 _res1 : 1;
        u8 fast_btb_capable : 1;
        u8 master_data_parity_err : 1;
        u8 devsel_timing : 2;
        u8 signaled_target_abrt : 1;
        u8 received_target_abrt : 1;
        u8 received_master_abrt : 1;
        u8 signaled_system_err : 1;
        u8 detected_parity_err : 1;
      } data;
      
      u16 raw;
    } status;

    u8 rev_id;
    u8 prog_if;
    u8 sub_class;
    class_code_t class_code : 8;

    u8 cache_line_size;
    u8 latency_timer;
    
    union {
      struct {
        u8 id : 7;
        u8 mf : 1; // multi functional
      } data;
      
      u8 raw;
    } type;
    
    union {
      struct {
        u8 completion_code : 4;
        u8 _res0 : 2;
        u8 start_bist : 1;
        u8 bist_capable : 1;
      } data;
      
      u8 raw;
    } bist;
  } header;
  
  union {
    struct {
      bar_t bar0;
      bar_t bar1;
      bar_t bar2;
      bar_t bar3;
      bar_t bar4;
      bar_t bar5;
      u32 cardbus_cis_ptr;
      
      u16 subsystem_vendor_id;
      u16 subsystem_id;
      
      u32 exp_rom_base_addr;
      
      u8 capabilities_ptr;
      u32 _res0 : 24;
      
      u32 _res1;
      
      u8 int_line;
      u8 int_pin;
      u8 min_grant;
      u8 max_latency;
    } type0;
    
    struct {
      bar_t bar0;
      bar_t bar1;
      
      u8 primary_bus_num;
      u8 secondary_bus_num;
      u8 subordinate_bus_num;
      u8 secondary_latency_timer;
      
      u8 io_base;
      u8 io_limit;
      u16 secondary_status;
      
      u16 memory_base;
      u16 memory_limit;
      
      u16 prefetchable_mem_base;
      u16 prefetchable_mem_limit;
      
      u32 prefetchable_base_high;
      u32 prefetchable_base_low;
      
      u16 io_base_high;
      u16 io_limit_high;
      
      u8 capability_ptr;
      u32 _res0 : 24;
      
      u32 expansion_rom_base_addr;
      
      u8 int_line;
      u8 int_pin;
      u16 bridge_ctrl;
    } type1;
    
    struct {
      u32 cardbus_base_addr; // Socket / ExCa
      
      u8 capabilities_list_offset;
      u8 _res0;
      u16 secondary_status;
      
      u8 pci_bus_num;
      u8 cardbus_bus_num;
      u8 subordinate_bus_num;
      u8 cardbus_latency_timer;
      
      u32 mem_base_addr0;
      u32 mem_limit0;
      
      u32 mem_base_addr1;
      u32 mem_limit1;
      
      u32 io_base_addr0;
      u32 io_limit0;
      
      u32 io_base_addr1;
      u32 io_limit1;
      
      u8 int_line;
      u8 int_pin;
      u16 bridge_ctrl;
      
      u16 subsystem_device_id;
      u16 subsystem_vendor_id;
      
      u32 pc_card_legacy_base_addr;
    } type2;
  } data; 
} pci_entry_t;

void pci_scan(void);
const pci_entry_t* pci_get_device(u32 vendor, u32 device);

#endif /* PCI_H_ */
