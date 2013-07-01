#ifndef RTC_H_
#define RTC_H_

#include <types.h>

typedef struct {
	u16 seconds;
	u16 minutes;
	u16 hours;
	u16 weekday;
	u16 day;
	u16 month;
	u16 year;
	u16 century;
} rtc_datetime_t;

void rtc_get_datetime(rtc_datetime_t *dt);
void rtc_sleep(u16 seconds);

#endif /* RTC_H_ */
