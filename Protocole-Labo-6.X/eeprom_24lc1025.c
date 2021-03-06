#include "eeprom_24lc1025.h"

void eeprom_24lc1025_write(char addr_i2c, int addr, char data) {
    StartI2C();
    IdleI2C();
    WriteI2C(addr_i2c);
    WriteI2C((char) (addr >> 8));
    WriteI2C((char) (addr & 0x00ff));
    WriteI2C(data);
    StopI2C();
    IdleI2C();
}

void eeprom_24lc1025_writeArray(char addr_i2c, int addr, char *data, char size) {
    char i = 0;
    StartI2C();
    IdleI2C();
    WriteI2C(addr_i2c);
    WriteI2C((char) (addr >> 8));
    WriteI2C((char) (addr & 0x00ff));
    for (i = 0; i < size; i++) {
        WriteI2C(data[i]);
    }
    StopI2C();
    IdleI2C();
}

char eeprom_24lc1025_read(char addr_i2c, int addr) {
    char data = 0;
    StartI2C();
    IdleI2C();
    WriteI2C(addr_i2c);
    WriteI2C((char) (addr >> 8));
    WriteI2C((char) (addr & 0x00ff));
    RestartI2C();
    IdleI2C();
    WriteI2C(addr_i2c | 0x01);
    data = ReadI2C();
    NotAckI2C();
    StopI2C();
    IdleI2C();
    return data;
}

void eeprom_24lc1025_readArray(char addr_i2c, int addr, char *data, char size) {
    char i = 0;
    StartI2C();
    IdleI2C();
    WriteI2C(addr_i2c);
    WriteI2C((char) (addr >> 8));
    WriteI2C((char) (addr & 0x00ff));
    RestartI2C();
    IdleI2C();
    WriteI2C(addr_i2c | 0x01);
    for (i = 0; i < size; i++) {
        data[i] = ReadI2C();
        if (i < size - 1) {
            AckI2C();
        } else {
            NotAckI2C();
        }
    }
    StopI2C();
    IdleI2C();
}
