/* 
 * File:   eeprom_24lc1025.h
 * Author: a.linteau
 *
 * Created on 15 avril 2014, 13:08
 */

#ifndef EEPROM_24LC1025_H
#define	EEPROM_24LC1025_H

#include <plib/i2c.h>

#ifdef	__cplusplus
extern "C" {
#endif

    void eeprom_24lc1025_write(char addr_i2c, char addr, char data);
    void eeprom_24lc1025_writeArray(char addr_i2c, char addr, char *data, char size);

    char eeprom_24lc1025_read(char addr_i2c, char addr);
    void eeprom_24lc1025_readArray(char addr_i2c, char addr, char *data, char size);

#ifdef	__cplusplus
}
#endif

#endif	/* EEPROM_24LC1025_H */

