#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "primegen.h"


int encrRSA(int binint) //binint = number from converting binary in a int and back
{   

    int x1 = generate_random_prime;
    int x2 = generate_random_prime;

    int encrmod = x1 + x2;      //modulus of both prime numbers
    int len = (x1-1) * (x2-1);  //lenght of all numbers between 1 and modulus with common factors removed
    int cplen = len;
    int cpmod = encrmod - 1;
    bool notcprime;
    bool cprime1, cprime2;
    int rangeup,rangelow;
    
    while(cprime1 == false || cprime2 == false)
    {
        cplen--;                                
        cprime1 = are_coprime(cplen,len);
        cprime2 = are_coprime(cplen,encrmod);
        /*if (cplen < 2)
        {
            !!Implement code here to generate two new prime numbers /start again
        }
        */                             
    }

    int encryptint = (pow(binint,cplen)) ;

    printf("The file was just encrypted with the private Encryption Key: %d\n",&cplen);
    
    printf("The Public encryption keys are (they are common factors of the private key ):"); //give out public keys in certain range following the rule: decryptor = common factor of cplen
    for (int v = 2 ; v<= 100; v++)
    {
        if(cplen % v == 0 )
        {
            printf(" %d,",v);
        } 
    }
    printf("\n");
    printf("The encryption and decryption Modulus is %d", encrmod);
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
}
