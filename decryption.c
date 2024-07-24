#include <stdio.h>
#include "encryption.h"
#include "RSAencryption.h"
#include "conversion.h"

void decrCeaser(unsigned char* binaryString);
void decrRSA(unsigned char* binaryString); 

void decrCeaser(unsigned char* binaryString)
{
    encrCaeser(binaryString);
}

void decrRSA(unsigned char* binaryString)
{
    unsigned long long int n, e, d;

    printf("Public Key(n,d): ");
    scanf_s("%lld,%lld",&n,&d);

    unsigned long long int cipher = binaryStringToInt(binaryString);
    unsigned long long int RSAcypher = rsaDecrypt(cipher,d,n);
    binaryString = intToBinaryString(RSAcypher);

    printf("----File decryption completed-----\n");
}   