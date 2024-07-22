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

// Function to generate a random prime number within a specified range
int generate_random_prime() {
    int numb;
    do {
        numb = generate_random_number(2, 50); //range in which the primes are generated
    } while (!is_prime(numb));

    return numb;
}



// Function to compute the greatest common divisor (GCD) using the Euclidean algorithm
int gcd(int a, int b) { //a = biggest coprime
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to check if two numbers are coprime
bool are_coprime(int copr1, int copr2) {
    if (gcd(copr1, copr2) == 1)
    {
        return true;
    }else
    {
        return false;
    }
}

