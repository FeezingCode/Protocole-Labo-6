#ifndef RTC_DS1307_H
#define	RTC_DS1307_H

#define RTC_DS1307_TIME_I2C_ADDR    0xD0

#define RTC_DS1307_DATE_TIME_ARRAY_SIZE 7

#define RTC_DS1307_TIME_ARRAY_SIZE  3
#define RTC_DS1307_TIME_ARRAY_SEC   0
#define RTC_DS1307_TIME_ARRAY_MIN   1
#define RTC_DS1307_TIME_ARRAY_HR    2

#define RTC_DS1307_DATE_ARRAY_SIZE  4
#define RTC_DS1307_DATE_ARRAY_DAY   0
#define RTC_DS1307_DATE_ARRAY_DATE  1
#define RTC_DS1307_DATE_ARRAY_MONTH 2
#define RTC_DS1307_DATE_ARRAY_YEAR  3

#define RTC_DS1307_REGISTER_SEC     0x00
#define RTC_DS1307_REGISTER_MIN     0x01
#define RTC_DS1307_REGISTER_HR      0x02
#define RTC_DS1307_REGISTER_DAY     0x03
#define RTC_DS1307_REGISTER_DATE    0x04
#define RTC_DS1307_REGISTER_MONTH   0x05
#define RTC_DS1307_REGISTER_YEAR    0x06
#define RTC_DS1307_REGISTER_CTRL    0x07

#define RTC_DS1307_HR_FORMAT_12H    1
#define RTC_DS1307_HR_FORMAT_24H    0

#define RTC_DS1307_SQW_FREQ_1HZ     0x10
#define RTC_DS1307_SQW_FREQ_4KHZ    0x11
#define RTC_DS1307_SQW_FREQ_8KHZ    0x12
#define RTC_DS1307_SQW_FREQ_32KHZ   0x13
#define RTC_DS1307_SQW_OUT_1        0x00
#define RTC_DS1307_SQW_OUT_0        0x80

#include <plib/i2c.h>

#ifdef	__cplusplus
extern "C" {
#endif

    char rtc_DS1307_BCD_to_binary(char bcd);
    char rtc_DS1307_binary_to_BCD(char binary);

    char rtc_DS1307_readDateTime(char* data);
    char rtc_DS1307_readTime(char* time);
    void rtc_DS1307_readDate(char* date);

    void rtc_DS1307_writeDateTime(char* data, char hourFormat, char pm);
    void rtc_DS1307_writeTime(char* time, char hourFormat, char pm);
    void rtc_DS1307_writeDate(char* date);

    void rtc_DS1307_setSQW(char config);

    char rtc_DS1307_readRAM(char addr_data);
    void rtc_DS1307_writeRAM(char addr_data, char data);

#ifdef	__cplusplus
}
#endif

#endif	/* RTC_DS1307_H */

