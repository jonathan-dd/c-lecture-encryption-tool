#ifndef RSAENCRYPTION_H
#define RSAENCRYPTION_H

unsigned long long int rsaEncrypt(unsigned long long int message, unsigned long long int e, unsigned long long int n);
unsigned long long int rsaDecrypt(unsigned long long int cipher, unsigned long long int d, unsigned long long int n);

#endif