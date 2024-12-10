#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Function to calculate gcd
int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Function to perform modular exponentiation
long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

// Function to generate keys
void generate_keys(int *n, int *e, int *d) {
   // int p = 61; // First prime number (for simplicity, use small primes)
    //int q = 53; // Second prime number
    int p, q;
    printf("Enter two prime numbers:\n");
    scanf("%d%d",&p,&q);
    *n = p * q;
    int phi = (p - 1) * (q - 1);

    // Choose e
    *e = 2;
    while (*e < phi) {
        if (gcd(*e, phi) == 1) {
            break;
        }
        (*e)++;
    }

    // Choose d
    *d = 1;
    while ((*d * *e) % phi != 1) {
        (*d)++;
    }
}

// Function to encrypt message
long long encrypt(int msg, int e, int n) {
    return mod_exp(msg, e, n);
}

// Function to decrypt message
long long decrypt(long long cipher, int d, int n) {
    return mod_exp(cipher, d, n);
}

int main() {
    int n, e, d;
    generate_keys(&n, &e, &d);

    printf("Public Key: (%d, %d)\n", e, n);
    printf("Private Key: (%d, %d)\n", d, n);

    int message;
    printf("Enter a message to encrypt (as an integer): ");
    scanf("%d", &message);

    long long encrypted_msg = encrypt(message, e, n);
    printf("Encrypted Message: %lld\n", encrypted_msg);

    long long decrypted_msg = decrypt(encrypted_msg, d, n);
    printf("Decrypted Message: %lld\n", decrypted_msg);

    return 0;
}
