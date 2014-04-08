#include "rtc_DS1307.h"

char rtc_DS1307_readDateTime(char addr_i2c, char* data) {
    char i = 0;
    char tmp = 0;
    char hourFormat;
    StartI2C();
    WriteI2C(addr_i2c);
    WriteI2C(RTC_DS1307_REGISTER_SEC);
    for (i = 0; i < RTC_DS1307_DATE_TIME_ARRAY_SIZE; i++) {
        if (i == RTC_DS1307_TIME_ARRAY_SEC) {
            data[RTC_DS1307_TIME_ARRAY_SEC] =
                    rtc_DS1307_BCD_to_binary(ReadI2C() & 0x7F);
        } else if (i == RTC_DS1307_TIME_ARRAY_HR) {
            tmp = ReadI2C();
            hourFormat = tmp & (1 << 6);
            if (hourFormat) {//12 hour
                hourFormat = tmp & (1 << 5);
                tmp &= 0x1F;
            } else {
                tmp &= 0x3F;
            }
            data[RTC_DS1307_TIME_ARRAY_HR] = tmp;
        } else {
            data[i] = rtc_DS1307_BCD_to_binary(ReadI2C());
        }
    }
    IdleI2C();
    return hourFormat;
}

char rtc_DS1307_readTime(char addr_i2c, char* time) {
    char i = 0;
    char tmp = 0;
    char hourFormat;
    StartI2C();
    WriteI2C(addr_i2c);
    WriteI2C(RTC_DS1307_REGISTER_SEC);
    for (i = 0; i < RTC_DS1307_TIME_ARRAY_SIZE; i++) {
        if (i == RTC_DS1307_TIME_ARRAY_SEC) {
            time[RTC_DS1307_TIME_ARRAY_SEC] =
                    rtc_DS1307_BCD_to_binary(ReadI2C() & 0x7F);
        } else if (i == RTC_DS1307_TIME_ARRAY_HR) {
            tmp = ReadI2C();
            hourFormat = tmp & (1 << 6);
            if (hourFormat) {//12 hour
                hourFormat = tmp & (1 << 5);
                tmp &= 0x1F;
            } else {
                tmp &= 0x3F;
            }
            time[RTC_DS1307_TIME_ARRAY_HR] = tmp;
        } else {
            time[i] = rtc_DS1307_BCD_to_binary(ReadI2C());
        }
    }
    IdleI2C();
    return hourFormat;
}

void rtc_DS1307_readDate(char addr_i2c, char* date) {
    char i = 0;
    char hourFormat;
    StartI2C();
    WriteI2C(addr_i2c);
    WriteI2C(RTC_DS1307_REGISTER_DAY);
    for (i = 0; i < RTC_DS1307_DATE_ARRAY_SIZE; i++) {
        date[i] = rtc_DS1307_BCD_to_binary(ReadI2C());
    }
    IdleI2C();
    return;
}

//void rtc_DS1307_writeDateTime(char addr_i2c, char* data, char hourFormat);
//void rtc_DS1307_writeTime(char addr_i2c, char* time, char hourFormat);
//void rtc_DS1307_writeDate(char addr_i2c, char* date);

//void rtc_DS1307_setSQW(char addr_i2c, char config);