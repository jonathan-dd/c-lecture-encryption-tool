#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Funktion zur Konvertierung einer Binärzeichenfolge in eine Ganzzahl
int binaryStringToInt(const char *binaryString) {
    unsigned long long int length = strlen(binaryString);
    unsigned long long int number = 0;
    for (int i = 0; i < length; i++) {
        if (binaryString[i] == '1') {
            number += pow(2, length - 1 - i);
        }
    }
    return number;
}

// Funktion zur Konvertierung einer Ganzzahl in eine Binärzeichenfolge
char* intToBinaryString(int number) {
    if (number == 0) {
        char *binaryString = (char*) malloc(2);
        strcpy(binaryString, "0");
        return binaryString;
    }

    int bits = (int)log2(number) + 1;
    char *binaryString = (char*) malloc(bits + 1);
    binaryString[bits] = '\0';

    for (int i = bits - 1; i >= 0; i--) {
        binaryString[i] = (number % 2) ? '1' : '0';
        number /= 2;
    }

    return binaryString;
}