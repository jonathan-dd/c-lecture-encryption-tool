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
    
    while(cprime1 == false || cprime2 == false)
    {
        cplen--;                                
        cprime1 = are_coprime(cplen,len);
        cprime2 = are_coprime(cplen,encrmod);
        /*if (cplen < 2)
        {
            !!Implement code here to generate two new prime numbers
        }
        */                             
    }

    int encryptint = (pow(binint,cplen)) ;


    printf("The file was just encrypted with the private Encryption Key: %d\n",&cplen);

}