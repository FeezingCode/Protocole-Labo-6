/* 
 * File:   main.c
 * Author: g.lagrange
 *
 * Created on 8 avril 2014, 10:55
 */

#define USE_OR_MASKS
#define _XTAL_FREQ 8000000
#define DOWNLOAD_BUTTON PORTBbits.RB4
#define MESURE_BUTTON PORTBbits.RB3

#include <xc.h>
#include <pic18.h>
#include <htc.h>
#include <plib/i2c.h>
#include <stdio.h>
#include <stdlib.h>    
#include "eeprom_24LC1025.h"
#include "rtc_DS1307.h"
#include "sensor_distance_SRF02.h"

#pragma config  OSC = INTIO67, BOREN = OFF, PWRT = ON
#pragma config  WDT = OFF, DEBUG = ON, LVP = OFF

void putch(char data); // Pour utiliser printf sur RS232
char getch(); // Pour utiliser sur RS232
char getche(); // Pour utiliser gets sur RS232


int main(int argc, char** argv) {
    char ds1307[7]; // registres 0 a 6 du ds1307
    char jours_sem[7][9] = {"dimanche", "lundi", "mardi", "mercredi", "jeudi", "vendredi", "samedi"};
    char config, spbrg;
    char rep[10];

    /********** Initialisation des registres **********/
    ???         // Aucune entree analogique
    ???    		// Oscillateur interne 8MHz
    ???         // Tx en sortie (on laisse les broches I2C en entrees, par defaut)

    // Pour la communication serie asynchrone (RS232 - 9600 baud)
    config = USART_TX_INT_OFF |
             USART_RX_INT_OFF |
             USART_ASYNCH_MODE |
             USART_EIGHT_BIT |
             USART_CONT_RX |
             USART_BRGH_LOW;
    spbrg = 12;         // a 8mhZ 12 -> 9600 BAUD
    OpenUSART(config, spbrg);

    // Pour la communication I2C
    ???		// I2C en mode MASTER avec vitesse compatible au DS1307
    ??? 	// Valeur de reload du compteur pour la generation de SCL: (Fosc/4)/Fscl - 1

/******** Fin de l'initialisation des registres ********/

      printf("\n\rLabo I2C: Appareil de mesure de distances\n\r");

// ---------- Affichage du temps du DS1307 sur terminal ---------------
	//lecture_ds1307(ds1307);
	printf("???",???); 	// Afficher jour-date-temps(sauf secondes)

	puts("Configuration de l'horloge (o/n)?");
	config = getch();

	if (config == 'o')
	{
		// Recuperer les informations puis les formater et les mettre a la bonne place dans le tableau "ds1307" - xtoi() peut etre tres utile
		// Attention aux bits speciaux du registre (CH, mode 24h...)
		printf("\n\rAnnee (XX)? ");
		gets(rep);
		???
		printf("Mois (XX)? ");
		gets(rep);
		???
		printf("Date (XX)? ");
		gets(rep);
		???
		printf("Jour de semaine 1-7 ? ");
		gets(rep);
		???
		printf("\n\rHeure 0-23 (XX)? ");
		gets(rep);
		???
		printf("Minutes 0-59 (XX)? ");
		gets(rep);
		???
		???	// registre des secondes: remettre les secondes a 0 plutot que de demander a l'usager

		ecriture_ds1307(ds1307);
		printf("\r\nTemps modifie avec succes!\r\n");
        printf("???",???); 	// Afficher jour-date-temps(sauf secondes)

	}

	printf("\r\nPret pour mesurer!\r\n");

	while(1)
	{
//		Contenu des seances du 18 et 25 mars
	}
    return (EXIT_SUCCESS);
}

void putch(char data){
    while(!TXIF);
    TXREG=data;
}

char getch(){
    while(!RCIF);
    return(RCREG);
}

char getche(){
    return(getch());
}