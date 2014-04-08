/* 
 * File:   eeprom_24LC1025.h
 * Author: a.linteau
 *
 * Created on 8 avril 2014, 09:55
 */

#ifndef EEPROM_24LC1025_H
#define	EEPROM_24LC1025_H

#include <plib/i2c.h>

#ifdef	__cplusplus
extern "C" {
#endif

    void eeprom_24LC102_write(char addr_i2c, int addr_data, void *data, int length);
    void eeprom_24LC102_read(char addr_i2c, int addr_data, void *buffer, int length);


#ifdef	__cplusplus
}
#endif

#endif	/* EEPROM_24LC1025_H */

