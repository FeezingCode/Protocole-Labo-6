/* 
 * File:   main.c
 * Author: g.lagrange & a.lineau
 *
 * Created on 8 avril 2014, 10:55
 */

#define USE_OR_MASKS
#define _XTAL_FREQ      8000000
#define BUFFER_SIZE     20
#define DOWNLOAD_BUTTON PORTBbits.RB4
#define MESURE_BUTTON   PORTBbits.RB3
#define RS232_CONFIG    USART_TX_INT_OFF | USART_RX_INT_OFF | USART_ASYNCH_MODE\
             | USART_EIGHT_BIT | USART_CONT_RX | USART_BRGH_LOW
#define RS232_PBRG      12

#include <xc.h>
#include <plib/i2c.h>
#include <stdio.h>
#include <stdlib.h>
#include "rtc_DS1307.h"
#include "sensor_distance_SRF02.h"

#pragma config  OSC = INTIO67, BOREN = OFF, PWRT = ON
#pragma config  WDT = OFF, DEBUG = ON, LVP = OFF

void putch(char data); // Pour utiliser printf sur RS232
char getch(); // Pour utiliser sur RS232
char getche(); // Pour utiliser gets sur RS232
char getData(char* buffer, char min, char max, char* invalidData);
char* fgets(char* str, int num);

int main(int argc, char** argv) {
    char buffer[BUFFER_SIZE] = {0};
    char ds1307_data[RTC_DS1307_DATE_TIME_ARRAY_SIZE]; // registres 0 a 6 du ds1307
    char ds1307_tmp_data[RTC_DS1307_DATE_TIME_ARRAY_SIZE];
    char weeks_day_french[7][9] = {"dimanche", "lundi", "mardi", "mercredi", "jeudi", "vendredi", "samedi"};
    //char weeks_day_english[7][10] = {"sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday"};;
    char user_input = 0;
    char invalidData = 0;
    int i = 0;

    OSCCON = 0b01110010;
    ADCON1 = 0xff;
    OpenUSART(RS232_CONFIG, RS232_PBRG); //9600 BAUD, rs232
    OpenI2C(MASTER, SLEW_ON);

    printf("\n\rLabo I2C: Appareil de mesure de distances\n\r");
    rtc_DS1307_readDateTime(ds1307_data);
    printf("%s, %d-%d-%d, %d:%d", weeks_day_french[ds1307_data[RTC_DS1307_DATE_ARRAY_DAY]],
            ds1307_data[RTC_DS1307_DATE_ARRAY_YEAR] + 2000, ds1307_data[RTC_DS1307_DATE_ARRAY_MONTH],
            ds1307_data[RTC_DS1307_DATE_ARRAY_DATE], ds1307_data[RTC_DS1307_TIME_ARRAY_HR],
            ds1307_data[RTC_DS1307_TIME_ARRAY_MIN]); // Afficher jour-date-temps(sauf secondes)
    puts("Configuration de l'horloge (o/n)?");
    user_input = getch();
    while (user_input != 'o' || user_input != 'n' || user_input != 0) {
        printf("\r\nCommande invalide! (o/n)\r\n");
        user_input = getch();
    }
    do {
        if (user_input == 'o') {
            // Recuperer les informations puis les formater et les mettre a la bonne place dans le tableau "ds1307" - xtoi() peut etre tres utile
            // Attention aux bits speciaux du registre (CH, mode 24h...)
            printf("\n\rAnnee (XX)? ");
            fgets(buffer, BUFFER_SIZE);
            getData(buffer, 0, 99, invalidData);

            printf("Mois (XX)? ");
            fgets(buffer, BUFFER_SIZE);
            getData(buffer, 1, 12, invalidData);

            printf("Date (XX)? ");
            fgets(buffer, BUFFER_SIZE);
            getData(buffer, 1, 31, invalidData);

            printf("Jour de semaine 1-7 ? ");
            fgets(buffer, BUFFER_SIZE);
            getData(buffer, 1, 7, invalidData);

            printf("\n\rHeure 0-23 (XX)? ");
            fgets(buffer, BUFFER_SIZE);
            getData(buffer, 0, 23, invalidData);

            printf("Minutes 0-59 (XX)? ");
            fgets(buffer, BUFFER_SIZE);
            getData(buffer, 0, 59, invalidData);

            ds1307_tmp_data[RTC_DS1307_REGISTER_SEC] = 0; // registre des secondes: remettre les secondes a 0 plutot que de demander a l'usager
            if (invalidData) {
                printf("\r\nCertaines donnees sont invalides\r\n");
                puts("Reconfigurer? (o/n)?");
                user_input = getch();
                while (user_input != 'o' || user_input != 'n' || user_input != 0) {
                    printf("\r\nCommande invalide! (o/n)\r\n");
                    user_input = getch();
                }
                if (user_input == 'n') {
                    invalidData = 0;
                }
            } else {
                for (i = 0; i < RTC_DS1307_DATE_TIME_ARRAY_SIZE; i++) {
                    ds1307_data[i] = ds1307_tmp_data[i];
                }
                rtc_DS1307_writeDateTime(ds1307_data, RTC_DS1307_HR_FORMAT_24H, 0);
                printf("\r\nTemps modifie avec succes!\r\n");
                printf("%s, %d-%d-%d, %d:%d", weeks_day_french[ds1307_data[RTC_DS1307_DATE_ARRAY_DAY]],
                        ds1307_data[RTC_DS1307_DATE_ARRAY_YEAR] + 2000, ds1307_data[RTC_DS1307_DATE_ARRAY_MONTH],
                        ds1307_data[RTC_DS1307_DATE_ARRAY_DATE], ds1307_data[RTC_DS1307_TIME_ARRAY_HR],
                        ds1307_data[RTC_DS1307_TIME_ARRAY_MIN]); // Afficher jour-date-temps(sauf secondes) // Afficher jour-date-temps(sauf secondes)
            }
        }
    } while (invalidData);
    printf("\r\nPret pour mesurer!\r\n");

    while (1) {
        //		Contenu des seances du 18 et 25 mars
    }
    return (EXIT_SUCCESS);
}

void putch(char data) {
    while (!TXIF);
    TXREG = data;
}

char getch() {
    while (!RCIF);
    return (RCREG);
}

char getche() {
    return (getch());
}

char getData(char* buffer, char min, char max, char* invalidData) {
    long tmp = 0;
    char isNumber = 0;
    tmp = strtol(buffer, isNumber, 0);
    if (isNumber) {
        if (tmp < min || tmp > max) {
            *invalidData = 1;
        }
    } else {
        *invalidData = 1;
    }
    return (char) tmp;
}

char* fgets(char* str, int num) {
    int i;
    int c;
    int done = 0;
    if (str == 0 || num <= 0) {
        return 0;
    }
    for (i = 0; !done && i < num - 1; i++) {
        c = getc();
        if (c == EOF) {
            done = 1;
            i--;
        } else {
            str[i] = c;
            if (c == '\n') {
                done = 1;
            }
        }
    }
    str[i] = '\0';
    if (i == 0) {
        return 0;
    } else {
        return str;
    }
}

//bob avec cheveu