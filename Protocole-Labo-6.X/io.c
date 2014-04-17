#include "io.h"
#include <xc.h>
#include <stdlib.h>

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

char getData(char* message, char* buffer, int buffer_size, char min, char max) {
    char invalidData = 0;
    char data = 0;
    printf(message);
    fgets(buffer, buffer_size);
    data = extractData(buffer, min, max, &invalidData);
    if(invalidData){
        return min;
    }
    return data;
}

char extractData(char* buffer, char min, char max, char* invalidData) {
    long tmp = 0;
    char isNumber = 0;
    tmp = strtol(buffer, &isNumber, 0);
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
        c = getch();
        if (c == EOF) {
            done = 1;
            i--;
        } else {
            str[i] = c;
            if (c == '\n' || c == '\0') {
                done = 1;
            }
        }
    }
    if (str[i - 1] != '\0') {
        str[i] = '\0';
    }
    if (i == 0) {
        return 0;
    } else {
        return str;
    }
}
