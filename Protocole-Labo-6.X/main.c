/* 
 * File:   main.c
 * Author: g.lagrange & a.lineau
 *
 * Created on 8 avril 2014, 10:55
 */

#include "eeprom_24lc1025.h"


#define USE_OR_MASKS

#define _XTAL_FREQ      8000000
#define RS232_CONFIG    USART_TX_INT_OFF | USART_RX_INT_OFF | USART_ASYNCH_MODE\
             | USART_EIGHT_BIT | USART_CONT_RX | USART_BRGH_LOW
#define RS232_PBRG      12

#define SRF02_I2C_ADDR              0xE0
#define EPPROM_24LC1025_I2C_ADDR    0xA0

#define BUFFER_SIZE                  20

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <plib/usart.h>
#include <plib/i2c.h>
#include "rtc_DS1307.h"
#include "sensor_distance_SRF02.h"
#include "io.h"

#pragma config  OSC = INTIO67, BOREN = OFF, PWRT = ON
#pragma config  WDT = OFF, DEBUG = ON, LVP = OFF

char uploadButtonFlag = 0;
char mesureButtonFlag = 0;
char eraseButtonFlag = 0;
char distanceSensorReadyFlag = 0;
char distanceSensorStartFlag = 0;
char distanceSensorCounter = 0;

void interrupt ISR();

int main(int argc, char** argv) {
    char buffer[BUFFER_SIZE] = {0};
    char ds1307_data[RTC_DS1307_DATE_TIME_ARRAY_SIZE]; // registres 0 a 6 du ds1307
    char weeks_day_french[7][9] = {"Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"};
    char user_input = 0;
    int i = 0;
    int j = 0;   
    int data = 0;
    unsigned char dataCount = 0;

    OSCCON = 0b01110010;
    ADCON1 = 0xff;
    T0CON = 0b11000001;
    INT0IF = 0;
    INT1IF = 0;
    INT2IF = 0;
    INTCON |= (1 << 7) | (1 << 4) | (1 << 5);
    INTCON2 &= ~((1 << 6) | (1 << 5) | (1 << 4));
    INTCON3 &= (1 << 3) | (1 << 4);
    RCON &= ~(1 << 7);
    CloseI2C();
    OpenUSART(RS232_CONFIG, RS232_PBRG); //9600 BAUD, rs232
    OpenI2C(MASTER, SLEW_OFF);
    SSPADD = 0x13; //SSPAD = Fosc/(4*Fscl)-1, 100 khz
    //    StartI2C();
    //    IdleI2C();
    //    WriteI2C(RTC_DS1307_TIME_I2C_ADDR);
    //    WriteI2C(RTC_DS1307_REGISTER_SEC);
    //    WriteI2C((0<<7));
    //    CloseI2C();
    //    IdleI2C();
    printf("\n\rLabo I2C: Appareil de mesure de distances\n\r");
    rtc_DS1307_readDateTime(ds1307_data);
    printf("%s, %d:%d, %d-%d-%d\n\r", weeks_day_french[ds1307_data[RTC_DS1307_DATE_TIME_ARRAY_DAY] - 1],
            ds1307_data[RTC_DS1307_DATE_TIME_ARRAY_HR], ds1307_data[RTC_DS1307_DATE_TIME_ARRAY_MIN],
            ds1307_data[RTC_DS1307_DATE_TIME_ARRAY_YEAR] + 2000, ds1307_data[RTC_DS1307_DATE_TIME_ARRAY_MONTH],
            ds1307_data[RTC_DS1307_DATE_TIME_ARRAY_DATE]); // Afficher jour-date-temps(sauf secondes)
    puts("Configuration de l'horloge (o/n)?");
    user_input = getch();
    if (user_input == 'o') {
        ds1307_data[RTC_DS1307_DATE_TIME_ARRAY_YEAR] =
                getData("\n\rAnnee 0-99? ", buffer, BUFFER_SIZE, 0, 99);
        ds1307_data[RTC_DS1307_DATE_TIME_ARRAY_MONTH] =
                getData("Mois 1-12? ", buffer, BUFFER_SIZE, 1, 12);
        ds1307_data[RTC_DS1307_DATE_TIME_ARRAY_DATE] =
                getData("Date 1-31? ", buffer, BUFFER_SIZE, 1, 31);
        ds1307_data[RTC_DS1307_DATE_TIME_ARRAY_DAY] =
                getData("Jour de semaine 1-7 ? ", buffer, BUFFER_SIZE, 1, 7);
        ds1307_data[RTC_DS1307_DATE_TIME_ARRAY_HR] =
                getData("\n\rHeure 0-23 ? ", buffer, BUFFER_SIZE, 0, 23);
        ds1307_data[RTC_DS1307_DATE_TIME_ARRAY_MIN] =
                getData("Minutes 0-59 ? ", buffer, BUFFER_SIZE, 0, 59);
        ds1307_data[RTC_DS1307_DATE_TIME_ARRAY_SEC] = 0; //Sec = default value, 0
        OpenI2C(MASTER, SLEW_OFF);
        rtc_DS1307_writeDateTime(ds1307_data, RTC_DS1307_HR_FORMAT_24H, 0);
        printf("\r\nTemps modifie avec succes!\r\n");
        printf("%s, %d:%d, %d-%d-%d", weeks_day_french[ds1307_data[RTC_DS1307_DATE_TIME_ARRAY_DAY] - 1],
                ds1307_data[RTC_DS1307_DATE_TIME_ARRAY_HR], ds1307_data[RTC_DS1307_DATE_TIME_ARRAY_MIN],
                ds1307_data[RTC_DS1307_DATE_TIME_ARRAY_YEAR] + 2000, ds1307_data[RTC_DS1307_DATE_TIME_ARRAY_MONTH],
                ds1307_data[RTC_DS1307_DATE_TIME_ARRAY_DATE]);
    }
    printf("\r\nPret pour mesurer!\r\n");
    OpenI2C(MASTER, SLEW_OFF);
    dataCount = eeprom_24lc1025_read(EPPROM_24LC1025_I2C_ADDR, 0);
    while (1) {
        if (uploadButtonFlag) {
            uploadButtonFlag = 0;
            for (i = 0; i < dataCount; i++) {
                OpenI2C(MASTER, SLEW_OFF);
                eeprom_24lc1025_readArray(EPPROM_24LC1025_I2C_ADDR, 1 + i * 9, buffer, 9);
                data = ((int) buffer[0] << 7 )| (int) buffer[1];
                for (j = 0; j < RTC_DS1307_DATE_TIME_ARRAY_SIZE; j++) {
                    ds1307_data[i] = buffer[j + 2];
                }
                printf("\r\nMesure #%d : %d cm (%d:%d, %d-%d-%d)", i, data,
                        ds1307_data[RTC_DS1307_DATE_TIME_ARRAY_HR], ds1307_data[RTC_DS1307_DATE_TIME_ARRAY_MIN],
                        ds1307_data[RTC_DS1307_DATE_TIME_ARRAY_YEAR] + 2000, ds1307_data[RTC_DS1307_DATE_TIME_ARRAY_MONTH],
                        ds1307_data[RTC_DS1307_DATE_TIME_ARRAY_DATE]);
            }
        }
        if (mesureButtonFlag) {
            mesureButtonFlag = 0;
            data = sensor_distance_SRF02_getDistance(SRF02_I2C_ADDR, &distanceSensorReadyFlag,
                    &distanceSensorStartFlag);
            printf("\r\n Lecture #%d, %d cm", dataCount, data);
            OpenI2C(MASTER, SLEW_OFF);
            rtc_DS1307_readDateTime(ds1307_data);
            buffer[0] = (char) (data >> 7);
            buffer[1] = (char) (0x00ff & data);
            for (i = 0; i < RTC_DS1307_DATE_TIME_ARRAY_SIZE; i++) {
                buffer[i + 2] = ds1307_data[i];
            }            
            OpenI2C(MASTER, SLEW_OFF);
            eeprom_24lc1025_write(EPPROM_24LC1025_I2C_ADDR, 0, dataCount);
            OpenI2C(MASTER, SLEW_OFF);
            eeprom_24lc1025_writeArray(EPPROM_24LC1025_I2C_ADDR, 1 + dataCount * 9, buffer, 9);
            dataCount++;
        }
        if (eraseButtonFlag) {
            eraseButtonFlag = 0;
            dataCount = 0;
            OpenI2C(MASTER, SLEW_OFF);
            eeprom_24lc1025_write(EPPROM_24LC1025_I2C_ADDR, 0, 0);
        }
    }
    return (EXIT_SUCCESS);
}

void interrupt ISR() {
    if (INTCON & (1 << 2)) {//Timer 0
        INTCON &= ~(1 << 2);
        if (distanceSensorCounter > 0) {//Count approximately 74,752 ms
            distanceSensorCounter--;
            if (distanceSensorCounter == 0) {
                distanceSensorReadyFlag = 1;
            }
        }
        if (distanceSensorStartFlag) {
            distanceSensorStartFlag = 0;
            distanceSensorCounter = 146; //Set the counter for approximately 74,752 ms
        }
    }
    if (INTCON & (1 << 1)) {//INT0
        INTCON &= ~(1 << 1);
        mesureButtonFlag = 1;
    }
    if (INTCON3 & (1 << 0)) {//INT1
        INTCON3 &= ~(1 << 0);
        uploadButtonFlag = 1;
    }
    if (INTCON3 & (1 << 1)) {//INT2
        INTCON3 &= ~(1 << 1);
        eraseButtonFlag = 1;
    }
}
