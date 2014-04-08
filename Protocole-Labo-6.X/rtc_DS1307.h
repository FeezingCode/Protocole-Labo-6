#ifndef RTC_DS1307_H
#define	RTC_DS1307_H

#define RTC_DS1307_TIME_I2C_ADDR    0b11010000

#define RTC_DS1307_TIME_ARRAY_SIZE  3
#define RTC_DS1307_TIME_ARRAY_SEC   0
#define RTC_DS1307_TIME_ARRAY_MIN   1
#define RTC_DS1307_TIME_ARRAY_HR    2

#define RTC_DS1307_DATE_ARRAY_SIZE  4
#define RTC_DS1307_DATE_ARRAY_DAY   0
#define RTC_DS1307_DATE_ARRAY_DATE  1
#define RTC_DS1307_DATE_ARRAY_MONTH 2
#define RTC_DS1307_DATE_ARRAY_YEAR  3

#include <plib/i2c.h>

#ifdef	__cplusplus
extern "C" {
#endif

    void rtc_DS1307_readDateTime(char addr_i2c, char* data, char hourFormat);
    void rtc_DS1307_readTime(char addr_i2c, char* time, char hourFormat);
    void rtc_DS1307_readDate(char addr_i2c, char* date);

    void rtc_DS1307_writeDateTime(char addr_i2c, char* data, char hourFormat);
    void rtc_DS1307_writeTime(char addr_i2c, char* time, char hourFormat);
    void rtc_DS1307_writeDate(char addr_i2c, char* date);

    void rtc_DS1307_setSQW(char addr_i2c, char config);

    char rtc_DS1307_readRAM(char addr_i2c, char addr_data);
    void rtc_DS1307_writeRAM(char addr_i2c, char addr_data, char data);

#ifdef	__cplusplus
}
#endif

#endif	/* RTC_DS1307_H */

