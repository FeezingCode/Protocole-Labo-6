#ifndef RTC_DS1307_H
#define	RTC_DS1307_H

#include <plib/i2c.h>

#ifdef	__cplusplus
extern "C" {
#endif

void rtc_DS1307_readTime(char addr_i2c, char* time);


#ifdef	__cplusplus
}
#endif

#endif	/* RTC_DS1307_H */

