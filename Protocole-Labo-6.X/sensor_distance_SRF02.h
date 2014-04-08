/* 
 * File:   sensor_distance_SRF02.h
 * Author: a.linteau
 *
 * Created on 8 avril 2014, 09:55
 */

#ifndef SENSOR_DISTANCE_SRF02_H
#define	SENSOR_DISTANCE_SRF02_H

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

