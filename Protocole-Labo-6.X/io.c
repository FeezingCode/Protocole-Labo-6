#include "io.h"


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
