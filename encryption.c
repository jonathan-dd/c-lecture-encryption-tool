#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "RSAencryption.h"
#include "conversion.h"


void encrRSA(const char* binaryString) 
{   
    unsigned long long int n, e, d;
    generateRSAKeys(&n, &e, &d);

    unsigned long long int message = binaryStringToInt(binaryString);
    unsigned long long int RSAcypher = rsaEncrypt(message,e,n);
    binaryString = intToBinaryString(RSAcypher);

    printf("----File encryption completed-----\n");
    printf("Private Key: (n = %llu, e = %llu)\n", n, e);
    printf("Public Key: (n = %llu, d = %llu)\n", n, d);
}

void encrCaeser(char* binaryString)
{
    int length = strlen(binaryString);
    
    for (int i = 0; i < length; i++) {
        if (binaryString[i] == '0') {
            binaryString[i] = '1';
        } else if (binaryString[i] == '1') {
            binaryString[i] = '0';
        }
    }
    printf("----File encryption completed-----\n");
}
