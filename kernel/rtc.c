#include "rtc.h"

#include "utils.h"

/*typedef struct {
	u16 seconds;
	u16 minutes;
	u16 hours;
	u16 weekday;
	u16 day;
	u16 month;
	u16 year;
	u16 century;
} rtc_datetime_t; */

enum {
  RTCR_SEC = 0,
  RTCR_MIN = 2,
  RTCR_HOURS = 4,
  RTCR_WEEKDAY = 6,
  RTCR_DAY = 7,
  RTCR_MONTH = 8,
  RTCR_YEAR = 9,
  RTCR_CENTURY = 0x32,
  RTCR_STATUSA = 0xA,
  RTCR_STATUSB = 0xB
};

#define CMOS_P_REGSEL 0x70
#define CMOS_P_REGDAT 0x71

static u8 inline cmos_read(u8 reg) {
  outb(CMOS_P_REGSEL, 0x80 | reg);
  return inb(CMOS_P_REGDAT);
}

static void inline cmos_write(u8 reg, u8 data) {
  outb(CMOS_P_REGSEL, 0x80 | reg);
  outb(CMOS_P_REGDAT, data);
}

void rtc_get_datetime(rtc_datetime_t *dt) {
  if(dt == NULL) {
    return;
  }
  
  cmos_write(RTCR_STATUSB, 6); // bit 2 = 24h format, bit 4 = binary mode
  
  while(cmos_read(RTCR_STATUSA) & 0x80);
  
  dt->seconds = cmos_read(RTCR_SEC);
  dt->minutes = cmos_read(RTCR_MIN);
  dt->hours = cmos_read(RTCR_HOURS);
  dt->weekday = cmos_read(RTCR_WEEKDAY);
  dt->day = cmos_read(RTCR_DAY);
  dt->month = cmos_read(RTCR_MONTH);
  dt->year = cmos_read(RTCR_YEAR);
  dt->century = cmos_read(RTCR_CENTURY);
}

static inline u16 rtc_get_seconds(void) {
  return cmos_read(RTCR_SEC) + (cmos_read(RTCR_MIN) * 60) + (cmos_read(RTCR_HOURS) * 3600);
}

void rtc_sleep(u16 seconds) {
  u16 delta=0, start;
  
  start = rtc_get_seconds();
  
  while(delta < seconds) {
    delta = rtc_get_seconds() - start;
  }
}