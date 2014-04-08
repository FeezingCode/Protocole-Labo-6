#include "sensor_distance_SRF02.h"

void sensor_distance_SRF02_sendCommand(char addr_i2c, char command){
    StartI2C();
    WriteI2C(addr_i2c);
    WriteI2C(command);
    IdleI2C();
}
char sensor_distance_SRF02_readSoftwareRevision(char addr_i2c){
    char revision;
    StartI2C();
    WriteI2C(addr_i2c);
    WriteI2C(0);
    revision = ReadI2C();
    IdleI2C();
    return (int)revision;
}
int sensor_distance_SRF02_readDistance(char addr_i2c){
    char lsb;
    char msb;
    StartI2C();
    WriteI2C(addr_i2c);
    WriteI2C(2);
    msb = ReadI2C();
    lsb = ReadI2C();
    IdleI2C();
    return (int)((msb << 8) | lsb);
}