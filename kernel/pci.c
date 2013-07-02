#include <pci.h>
#include <utils.h>

#include <printf.h>

#define PCI_DEVICES 16

#define PCI_READ_HEADER_D1(d, o) pci_dev_table[pci_dev_it].header.d = pci_config_read(bus, dev, func, o);
#define PCI_READ_HEADER_D1_R(d, o) pci_dev_table[pci_dev_it].header.d.raw = pci_config_read(bus, dev, func, o);
#define PCI_READ_HEADER_D2(d1, d2, o) tmp = pci_config_read(bus, dev, func, o); \
                                                                pci_dev_table[pci_dev_it].header.d1 = tmp & 0x0FF; \
                                                                pci_dev_table[pci_dev_it].header.d2 = tmp >> 8;
                                                                
static pci_entry_t pci_dev_table[PCI_DEVICES] = {0};
static u8 pci_dev_it = 0;

static void pci_check_device(u8 bus, u8 dev, u8 func);
static inline void pci_check_device_type0(u8 bus, u8 dev, u8 func);
static inline void pci_check_device_type1(u8 bus, u8 dev, u8 func);
static inline void pci_check_device_type2(u8 bus, u8 dev, u8 func);

static u16 pci_config_read(u8 bus, u8 dev, u8 func, u8 reg) {
  const u16 CONFIG_ADDRESS = 0xCF8;
  const u16 CONFIG_DATA = 0xCFC;
  
  outl(CONFIG_ADDRESS, (0x80000000 | (bus << 16) | (dev << 11) | (func << 8) | (reg & 0xFC)));
  return inl(CONFIG_DATA) >> ((reg & 2) * 8) & 0xFFFF;
} 

void pci_scan(void) {
  for(u8 bus=0; bus<255 && pci_dev_it < PCI_DEVICES; bus++) {
    for(u8 dev=0; dev<32 && pci_dev_it < PCI_DEVICES; dev++) {
      pci_dev_table[pci_dev_it].header.vendor_id = pci_config_read(bus, dev, 0, 0);

      if(pci_dev_table[pci_dev_it].header.vendor_id != 0xFFFF) {
        pci_check_device(bus, dev, 0);
      }
    } // dev
  } // bus
}

static void pci_check_device(u8 bus, u8 dev, u8 func) {
  u16 tmp;
  
  if(dev >= 32 && func >= 8) {
    return;
  }
  
  PCI_READ_HEADER_D1(device_id, 2);
  PCI_READ_HEADER_D1_R(command, 4);
  PCI_READ_HEADER_D1_R(status, 6);
  
  PCI_READ_HEADER_D2(rev_id, prog_if, 8);
  PCI_READ_HEADER_D2(sub_class, class_code, 0xA);
  
  PCI_READ_HEADER_D2(cache_line_size, latency_timer, 0xC);
  
  tmp = pci_config_read(bus, dev, func, 0xE);
  pci_dev_table[pci_dev_it].header.type.raw = tmp & 0x0FF;
  pci_dev_table[pci_dev_it].header.bist.raw = tmp >> 8;
  
/*  k_printf("#%d -> %x:%x type: %x (bus: %x, dev: %x, func: %x, mf: %s)\n", 
    pci_dev_it + 1,
    pci_dev_table[pci_dev_it].header.vendor_id, pci_dev_table[pci_dev_it].header.device_id, tmp & ~0xFF80,
    bus, dev, func,
    pci_dev_table[pci_dev_it - 1].header.type.data.mf == 1 ? "yes" : "no");*/
    
    switch(pci_dev_table[pci_dev_it].header.type.data.id) {
      case 0: pci_check_device_type0(bus, dev, func); break;
      case 1: pci_check_device_type1(bus, dev, func); break;
      case 2: pci_check_device_type2(bus, dev, func); break;
      default: return;
    }
    
  ++pci_dev_it;
  
  if(pci_dev_table[pci_dev_it - 1].header.type.data.mf == 1 && func == 0) {
    for(u8 i = func + 1; i < 8; i++) {
      pci_dev_table[pci_dev_it].header.vendor_id = pci_config_read(bus, dev, i, 0);
    
      if(pci_dev_table[pci_dev_it].header.vendor_id != 0xFFFF) {
        pci_check_device(bus, dev, i);
      }
    }
  }
}

static inline void pci_check_device_type0(u8 bus, u8 dev, u8 func) {
  u16 tmp;
  
  pci_dev_table[pci_dev_it].data.type0.bar0.raw = ((pci_config_read(bus, dev, func, 0x12) << 16) | pci_config_read(bus, dev, func, 0x10));
  pci_dev_table[pci_dev_it].data.type0.bar1.raw = ((pci_config_read(bus, dev, func, 0x16) << 16) | pci_config_read(bus, dev, func, 0x14));
  pci_dev_table[pci_dev_it].data.type0.bar2.raw = ((pci_config_read(bus, dev, func, 0x1A) << 16) | pci_config_read(bus, dev, func, 0x18));
  pci_dev_table[pci_dev_it].data.type0.bar3.raw = ((pci_config_read(bus, dev, func, 0x1E) << 16) | pci_config_read(bus, dev, func, 0x1C));
  pci_dev_table[pci_dev_it].data.type0.bar4.raw = ((pci_config_read(bus, dev, func, 0x22) << 16) | pci_config_read(bus, dev, func, 0x20));
  pci_dev_table[pci_dev_it].data.type0.bar5.raw = ((pci_config_read(bus, dev, func, 0x26) << 16) | pci_config_read(bus, dev, func, 0x24));
  
  pci_dev_table[pci_dev_it].data.type0.cardbus_cis_ptr = pci_config_read(bus, dev, func, 0x2A) << 16 | pci_config_read(bus, dev, func, 0x28);

  pci_dev_table[pci_dev_it].data.type0.subsystem_vendor_id = pci_config_read(bus, dev, func, 0x2C);
  pci_dev_table[pci_dev_it].data.type0.subsystem_id = pci_config_read(bus, dev, func, 0x2E);
  
  pci_dev_table[pci_dev_it].data.type0.exp_rom_base_addr = pci_config_read(bus, dev, func, 0x32)  << 16|pci_config_read(bus, dev, func, 0x26);
  
  pci_dev_table[pci_dev_it].data.type0.capabilities_ptr = pci_config_read(bus, dev, func, 0x34) & 0xFF;

  tmp = pci_config_read(bus, dev, func, 0x3C);
  pci_dev_table[pci_dev_it].data.type0.int_line = tmp & 0x0FF;
  pci_dev_table[pci_dev_it].data.type0.int_pin = tmp >> 8;
    
  tmp = pci_config_read(bus, dev, func, 0x3E);
  pci_dev_table[pci_dev_it].data.type0.min_grant = tmp & 0x0FF;
  pci_dev_table[pci_dev_it].data.type0.max_latency = tmp >> 8;
}

static inline void pci_check_device_type1(u8 bus, u8 dev, u8 func) {
  // not needed right now
}

static inline void pci_check_device_type2(u8 bus, u8 dev, u8 func) {
  // not needed right now
}

const pci_entry_t* pci_get_device(u32 vendor, u32 device) {
  for(u32 i=0; i<pci_dev_it; i++) {
    if(pci_dev_table[i].header.vendor_id == vendor && pci_dev_table[i].header.device_id == device) {
      return (const pci_entry_t *)&pci_dev_table[i];
    }
  }
  
  return NULL;
}
