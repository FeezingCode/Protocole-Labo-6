#include "sensor_distance_SRF02.h"

void sensor_distance_SRF02_sendCommand(char addr_i2c, char command) {
    StartI2C();
    IdleI2C();
    WriteI2C(addr_i2c);
    WriteI2C(SENSOR_DISTANCE_SRF02_REGISTER_COMMAND);
    WriteI2C(command);
    CloseI2C();
    IdleI2C();
}

char sensor_distance_SRF02_readSoftwareRevision(char addr_i2c) {
    char revision;
    StartI2C();
    IdleI2C();
    WriteI2C(addr_i2c);
    WriteI2C(SENSOR_DISTANCE_SRF02_REGISTER_REVISION);
    RestartI2C();
    WriteI2C(addr_i2c | 0x01);
    revision = ReadI2C();
    CloseI2C();
    IdleI2C();
    return (int) revision;
}

int sensor_distance_SRF02_readDistance(char addr_i2c) {
    char lsb;
    char msb;
    StartI2C();
    IdleI2C();
    WriteI2C(addr_i2c);
    WriteI2C(SENSOR_DISTANCE_SRF02_REGISTER_RANGE_MSB);
    RestartI2C();
    WriteI2C(addr_i2c | 0x01);
    msb = ReadI2C();
    lsb = ReadI2C();
    CloseI2C();
    IdleI2C();
    return (int) ((msb << 8) | lsb);
}

int sensor_distance_SRF02_getDistance(char addr_i2c, char *distanceSensorReadyFlag, char *distanceSensorStartFlag) {
    sensor_distance_SRF02_sendCommand(addr_i2c, SENSOR_DISTANCE_SRF02_COMMAND_RANGE_CM);
    *distanceSensorStartFlag = 1;
    while (!(*distanceSensorReadyFlag));
    distanceSensorReadyFlag = 0;
    return sensor_distance_SRF02_readDistance(addr_i2c);
}