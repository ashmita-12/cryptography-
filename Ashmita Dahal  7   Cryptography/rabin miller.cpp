#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

long long mulmod(long long a, long long b, long long m);
long long modulo(long long base, long long e, long long m);
bool Miller(long long p, int iteration);

int main()
{
    // Seed the random number generator
    srand(time(NULL));

    do
    {
        int iteration = 10;
        long long num;
        printf("Enter integer to test primality: ");
        scanf("%lld", &num);
        if (Miller(num, iteration))
            printf("%lld is prime\n", num);
        else
            printf("%lld is not prime\n", num);

        char choice;
        printf("Do you want to continue? (y/n): ");
        scanf(" %c", &choice); // Note the space before %c to consume any trailing newline character
        if (choice == 'n' || choice == 'N')
            break;

    } while (true);
    return 0;
}

// It returns true if number is prime otherwise false
long long mulmod(long long a, long long b, long long m)
{
    long long x = 0, y = a % m;
    while (b > 0)
    {
        if (b % 2 == 1)
        {
            x = (x + y) % m;
        }
        y = (y * 2) % m;
        b /= 2;
    }
    return x % m;
}

long long modulo(long long base, long long e, long long m)
{
    long long x = 1;
    long long y = base;
    while (e > 0)
    {
        if (e % 2 == 1)
            x = (x * y) % m;
        y = (y * y) % m;
        e = e / 2;
    }
    return x % m;
}

bool Miller(long long p, int iteration)
{
    if (p < 2)
    {
        return false;
    }
    if (p != 2 && p % 2 == 0)
    {
        return false;
    }
    long long s = p - 1;
    while (s % 2 == 0)
    {
        s /= 2;
    }
    for (int i = 0; i < iteration; i++)
    {
        long long a = rand() % (p - 1) + 1;
        long long temp = s;
        long long mod = modulo(a, temp, p);
        while (temp != p - 1 && mod != 1 && mod != p - 1)
        {
            mod = mulmod(mod, mod, p);
            temp *= 2;
        }
        if (mod != p - 1 && temp % 2 == 0)
        {
            return false;
        }
    }
    return true;
}
