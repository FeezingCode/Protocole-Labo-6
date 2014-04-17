/* 
 * File:   io.h
 * Author: a.linteau
 *
 * Created on 15 avril 2014, 13:00
 */

#ifndef IO_H
#define	IO_H

#include <stdio.h>

#ifdef	__cplusplus
extern "C" {
#endif

void putch(char data); // Pour utiliser printf sur RS232
char getch(); // Pour utiliser sur RS232
char getche(); // Pour utiliser gets sur RS232
char getData(char* message, char* buffer, int buffer_size, char min, char max);
char extractData(char* buffer, char min, char max, char* invalidData);
char* fgets(char* str, int num);


#ifdef	__cplusplus
}
#endif

#endif	/* IO_H */

