#ifndef SENSOR_DISTANCE_SRF02_H
#define	SENSOR_DISTANCE_SRF02_H

#define SENSOR_DISTANCE_SRF02_REGISTER_REVISION     0x00
#define SENSOR_DISTANCE_SRF02_REGISTER_COMMAND      0x00
#define SENSOR_DISTANCE_SRF02_REGISTER_RANGE_MSB    0x02
#define SENSOR_DISTANCE_SRF02_REGISTER_RANGE_LSB    0x03
#define SENSOR_DISTANCE_SRF02_REGISTER_AUTOTUNE_MSB 0x04
#define SENSOR_DISTANCE_SRF02_REGISTER_AUTOTUNE_LSB 0x05

#define SENSOR_DISTANCE_SRF02_COMMAND_RANGE_INCH    0x50
#define SENSOR_DISTANCE_SRF02_COMMAND_RANGE_CM      0x51
#define SENSOR_DISTANCE_SRF02_COMMAND_RANGE_USEC    0x52
#define SENSOR_DISTANCE_SRF02_COMMAND_FK_RANGE_INCH 0x56
#define SENSOR_DISTANCE_SRF02_COMMAND_FK_RANGE_CM   0x57
#define SENSOR_DISTANCE_SRF02_COMMAND_FK_RANGE_USEC 0x58
#define SENSOR_DISTANCE_SRF02_COMMAND_SEND_BURST    0x5C
#define SENSOR_DISTANCE_SRF02_COMMAND_AUTOTUNE      0x60
#define SENSOR_DISTANCE_SRF02_COMMAND_CHANGE_I2C_1  0xA0
#define SENSOR_DISTANCE_SRF02_COMMAND_CHANGE_I2C_2  0xA5
#define SENSOR_DISTANCE_SRF02_COMMAND_CHANGE_I2C_3  0xAA

#include <plib/i2c.h>

#ifdef	__cplusplus
extern "C" {
#endif

    void sensor_distance_SRF02_sendCommand(char addr_i2c, char command);
    char sensor_distance_SRF02_readSoftwareRevision(char addr_i2c);
    int sensor_distance_SRF02_readDistance(char addr_i2c);


#ifdef	__cplusplus
}
#endif

#endif	/* SENSOR_DISTANCE_SRF02_H */

