#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>


// Funktion zur modularen Exponentiation
unsigned long long int powerMod(unsigned long long int base, unsigned long long int exp, unsigned long long int mod) {
    unsigned long long int result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp = exp / 2;
    }
    return result;
}

// Funktion zur Berechnung des größten gemeinsamen Teilers (GCD)
unsigned long long int gcd(unsigned long long int a, unsigned long long int b) {
    while (b != 0) {
        unsigned long long int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Funktion zur Generierung von RSA-Schlüsseln
void generateRSAKeys(unsigned long long int *n, unsigned long long int *e, unsigned long long int *d) {
    unsigned long long int p = generatePrime();
    unsigned long long int q = generatePrime();
    *n = p * q;
    unsigned long long int phi = (p - 1) * (q - 1);

    do {
        *e = rand() % phi;
    } while (gcd(*e, phi) != 1);

    *d = findModInverse(*e, phi);
}

// Funktion zur RSA-Verschlüsselung
unsigned long long int rsaEncrypt(unsigned long long int message, unsigned long long int e, unsigned long long int n) {
    return powerMod(message, e, n);
}

// Funktion zur RSA-Entschlüsselung
unsigned long long int rsaDecrypt(unsigned long long int cipher, unsigned long long int d, unsigned long long int n) {
    return powerMod(cipher, d, n);
}

// Funktion zur Berechnung des modularen Inversen
unsigned long long int findModInverse(unsigned long long int a, unsigned long long int m) {
    unsigned long long int m0 = m, t, q;
    unsigned long long int x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}

// Funktion zur Generierung einer großen Primzahl (kleines Beispiel)
unsigned long long int generatePrime() {
    // Hier verwenden wir eine kleine, feste Primzahl. Für echte Anwendungen sollten größere Primzahlen verwendet werden.
    unsigned long long int primes[] = {101, 103, 107, 109, 113, 127, 131, 137, 139, 149};
    return primes[rand() % 10];
}

int main() {
    srand(time(NULL));

    unsigned long long int n, e, d;
    generateRSAKeys(&n, &e, &d);

    printf("Öffentlicher Schlüssel: (n = %llu, e = %llu)\n", n, e);
    printf("Privater Schlüssel: (n = %llu, d = %llu)\n", n, d);

    const char *binaryString = "10101001101011110000110000000000011111111001111000111001";
    unsigned long long int message = strtoull(binaryString, NULL, 2);
    printf("Originale Nachricht: %llu\n", message);

    unsigned long long int cipher = rsaEncrypt(message, e, n);
    printf("Verschlüsselte Nachricht: %llu\n", cipher);

    unsigned long long int decryptedMessage = rsaDecrypt(cipher, d, n);
    printf("Entschlüsselte Nachricht: %llu\n", decryptedMessage);

    return 0;
}