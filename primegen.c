#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Function to check if a number is prime
bool is_prime(int num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }
    return true;
}



// Function to generate random primes
void generate_random_primes(int *prime1, int *prime2) {
    int count = 0;
    int num;
    while (count < 2) {
        num = rand() % 1000 + 2; // Generate a random number between 2 and 101
        if (is_prime(num)) {
            if (count == 0) {
                *prime1 = num;
            } else {
                *prime2 = num;
            }
            count++;
        }
    }
    if(prime1>prime2)
    {
        prime1 = x2;
        prime2 = x1;
    }
    else
    {
        prime1 = x1;
        prime2 = x2;
    }
}

