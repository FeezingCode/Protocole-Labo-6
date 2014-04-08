/* 
 * File:   main.c
 * Author: g.lagrange & a.lineau
 *
 * Created on 8 avril 2014, 10:55
 */

#define USE_OR_MASKS
#define _XTAL_FREQ      8000000
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

int main(int argc, char** argv) {
    char ds1307[7]; // registres 0 a 6 du ds1307
    char weeks_day_french[7][9] = {"dimanche", "lundi", "mardi", "mercredi", "jeudi", "vendredi", "samedi"};
    char weeks_day_english[7][10] = {"sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday"};
    char rep[10];
    char config;
    OSCCON = 0b01110010;
    ADCON1 = 0xff;
    OpenUSART(RS232_CONFIG, RS232_PBRG); //9600 BAUD, rs232
    OpenI2C(MASTER, SLEW_ON);

    //printf("\n\rLabo I2C: Appareil de mesure de distances\n\r");

    // ---------- Affichage du temps du DS1307 sur terminal ---------------
    //lecture_ds1307(ds1307);
    //printf("???", ? ? ?); // Afficher jour-date-temps(sauf secondes)

    //puts("Configuration de l'horloge (o/n)?");
    //config = getch();

    //if (config == 'o') {
        // Recuperer les informations puis les formater et les mettre a la bonne place dans le tableau "ds1307" - xtoi() peut etre tres utile
        // Attention aux bits speciaux du registre (CH, mode 24h...)
        //printf("\n\rAnnee (XX)? ");
        //gets(rep);
        //? ? ?
        //printf("Mois (XX)? ");
        //gets(rep);
        //? ? ?
        //printf("Date (XX)? ");
        //gets(rep);
        //? ? ?
        //printf("Jour de semaine 1-7 ? ");
        //gets(rep);
        //? ? ?
        //printf("\n\rHeure 0-23 (XX)? ");
        //gets(rep);
        //? ? ?
        //printf("Minutes 0-59 (XX)? ");
        //gets(rep);
        //? ? ?
        //? ? ? // registre des secondes: remettre les secondes a 0 plutot que de demander a l'usager

        //ecriture_ds1307(ds1307)
        //printf("\r\nTemps modifie avec succes!\r\n");
        //printf("???", ? ? ?); // Afficher jour-date-temps(sauf secondes)

    //}

    //printf("\r\nPret pour mesurer!\r\n");

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

//t