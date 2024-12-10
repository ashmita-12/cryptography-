#include <stdio.h>
int gcdExtended(int a, int b, int *x, int *y)
{
    if (a == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }

    int x1, y1; 
    int gcd = gcdExtended(b % a, a, &x1, &y1);

    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}

int modInverse(int a, int m)
{
    int x, y;
    int g = gcdExtended(a, m, &x, &y);

    if (g != 1)
    {
        printf("Inverse doesn't exist as gcd(%d, %d) = %d\n", a, m, g);
        return -1;
    }
    else
    {
        
        int res = (x % m + m) % m;
        printf("Multiplicative inverse of %d under modulo %d is %d\n", a, m, res);
        return res;
    }
}

int main()
{
    int a, m = 26;

    
    printf("Enter the number to find its multiplicative inverse modulo %d: ", m);
    scanf("%d", &a);

    
    if (a <= 0)
    {
        printf("Please enter a positive integer.\n");
        return 1;
    }

    
    modInverse(a, m);

    return 0;
}
