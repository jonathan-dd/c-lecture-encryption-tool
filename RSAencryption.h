#ifndef RSAENCRYPTION_H
#define RSAENCRYPTION_H

unsigned long long int powerMod(unsigned long long int base, unsigned long long int exp, unsigned long long int mod);
unsigned long long int gcd(unsigned long long int a, unsigned long long int b);
void generateRSAKeys(unsigned long long int *n, unsigned long long int *e, unsigned long long int *d);
unsigned long long int rsaEncrypt(unsigned long long int message, unsigned long long int e, unsigned long long int n);
unsigned long long int rsaDecrypt(unsigned long long int cipher, unsigned long long int d, unsigned long long int n);
unsigned long long int findModInverse(unsigned long long int a, unsigned long long int m);
unsigned long long int generatePrime();

#endif