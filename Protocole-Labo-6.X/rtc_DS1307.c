#include "rtc_DS1307.h"

char rtc_DS1307_BCD_to_binary(char bcd) {
    return (bcd >> 4)*10 + (bcd & 0xF0);
}

char rtc_DS1307_binary_to_BCD(char binary) {
    char bcd = binary % 10;
    binary /= 10;
    bcd |= (binary << 4);
    return bcd;
}

char rtc_DS1307_readDateTime(char* data) {
    char i = 0;
    char tmp = 0;
    char hourFormat = 0;
    StartI2C();
    IdleI2C();
    WriteI2C(RTC_DS1307_TIME_I2C_ADDR);
    WriteI2C(RTC_DS1307_REGISTER_SEC);
    RestartI2C();
    IdleI2C();
    WriteI2C(RTC_DS1307_TIME_I2C_ADDR | 0x01);
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
    CloseI2C();
    IdleI2C();
    return hourFormat;
}

char rtc_DS1307_readTime(char* time) {
    char i = 0;
    char tmp = 0;
    char hourFormat;
    StartI2C();
    IdleI2C();
    WriteI2C(RTC_DS1307_TIME_I2C_ADDR);
    WriteI2C(RTC_DS1307_REGISTER_SEC);
    RestartI2C();
    WriteI2C(RTC_DS1307_TIME_I2C_ADDR | 0x01);
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
    CloseI2C();
    IdleI2C();
    return hourFormat;
}

void rtc_DS1307_readDate(char* date) {
    char i = 0;
    StartI2C();
    IdleI2C();
    WriteI2C(RTC_DS1307_TIME_I2C_ADDR);
    WriteI2C(RTC_DS1307_REGISTER_DAY);
    RestartI2C();
    WriteI2C(RTC_DS1307_TIME_I2C_ADDR | 0x01);
    for (i = 0; i < RTC_DS1307_DATE_ARRAY_SIZE; i++) {
        date[i] = rtc_DS1307_BCD_to_binary(ReadI2C());
    }
    CloseI2C();
    IdleI2C();
    return;
}

void rtc_DS1307_writeDateTime(char* data, char hourFormat, char pm) {
    char i = 0;
    char tmp = 0;
    StartI2C();
    IdleI2C();
    WriteI2C(RTC_DS1307_TIME_I2C_ADDR);
    WriteI2C(RTC_DS1307_REGISTER_SEC);
    for (i = 0; i < RTC_DS1307_DATE_TIME_ARRAY_SIZE; i++) {
        if (i == RTC_DS1307_TIME_ARRAY_SEC) {
            WriteI2C(rtc_DS1307_binary_to_BCD(data[RTC_DS1307_TIME_ARRAY_SEC]));
        } else if (i == RTC_DS1307_TIME_ARRAY_HR) {
            tmp = rtc_DS1307_binary_to_BCD(data[RTC_DS1307_TIME_ARRAY_HR]);
            if (hourFormat) {//12 hour                
                if (pm) {
                    tmp |= (1 << 5);
                }
                WriteI2C(tmp);
            } else {
                WriteI2C(tmp);
            }
            data[RTC_DS1307_TIME_ARRAY_HR] = tmp;
        } else {
            WriteI2C(data[i]);
        }
    }
    CloseI2C();
    IdleI2C();
}

void rtc_DS1307_writeTime(char* time, char hourFormat, char pm) {
    char i = 0;
    char tmp = 0;
    StartI2C();
    IdleI2C();
    WriteI2C(RTC_DS1307_TIME_I2C_ADDR);
    WriteI2C(RTC_DS1307_REGISTER_SEC);
    for (i = 0; i < RTC_DS1307_TIME_ARRAY_SIZE; i++) {
        if (i == RTC_DS1307_TIME_ARRAY_SEC) {
            WriteI2C(rtc_DS1307_binary_to_BCD(time[RTC_DS1307_TIME_ARRAY_SEC]));
        } else if (i == RTC_DS1307_TIME_ARRAY_HR) {
            tmp = rtc_DS1307_binary_to_BCD(time[RTC_DS1307_TIME_ARRAY_HR]);
            if (hourFormat) {//12 hour                
                if (pm) {
                    tmp |= (1 << 5);
                }
                WriteI2C(tmp);
            } else {
                WriteI2C(tmp);
            }
            time[RTC_DS1307_TIME_ARRAY_HR] = tmp;
        } else {
            WriteI2C(time[i]);
        }
    }
    CloseI2C();
    IdleI2C();
}

void rtc_DS1307_writeDate(char* date) {
    char i = 0;
    StartI2C();
    IdleI2C();
    WriteI2C(RTC_DS1307_TIME_I2C_ADDR);
    WriteI2C(RTC_DS1307_REGISTER_DATE);
    for (i = 0; i < RTC_DS1307_DATE_ARRAY_SIZE; i++) {
        WriteI2C(date[i]);
    }
    CloseI2C();
    IdleI2C();
}

