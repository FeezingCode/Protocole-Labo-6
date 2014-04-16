#include "eeprom_24lc1025.h"

void eeprom_24lc1025_write(char addr_i2c, char addr, char data) {
    StartI2C();
    IdleI2C();
    WriteI2C(addr_i2c | 0x01);
    WriteI2C(addr);

    CloseI2C();
    IdleI2C();
}

void eeprom_24lc1025_writeArray(char addr_i2c, char addr, char *data, char size) {
    StartI2C();
    IdleI2C();
    WriteI2C(addr_i2c | 0x01);
    WriteI2C(addr);

    CloseI2C();
    IdleI2C();
}

char eeprom_24lc1025_read(char addr_i2c, char addr) {
    StartI2C();
    IdleI2C();
    WriteI2C(addr_i2c);
    WriteI2C(addr);

    CloseI2C();
    IdleI2C();
}

void eeprom_24lc1025_readArray(char addr_i2c, char addr, char *data, char size) {
    StartI2C();
    IdleI2C();
    WriteI2C(addr_i2c);
    WriteI2C(addr);

    CloseI2C();
    IdleI2C();
}
