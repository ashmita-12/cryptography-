#include <stdio.h>

// C function for extended Euclidean Algorithm
int gcdExtended(int a, int b, int *x, int *y)
{
    printf("gcdExtended(a = %d, b = %d)\n", a, b); // Print current step

    // Base Case
    if (a == 0)
    {
        *x = 0;
        *y = 1;
        printf("Base case reached: gcd = %d, x = %d, y = %d\n", b, *x, *y);
        return b;
    }

    int x1, y1; // To store results of recursive call
    int gcd = gcdExtended(b % a, a, &x1, &y1);

    // Update x and y using results of recursive call
    *x = y1 - (b / a) * x1;
    *y = x1;

    printf("Updated x and y: gcd = %d, x = %d, y = %d\n", gcd, *x, *y); // Print updated x and y

    return gcd;
}

// Driver Program
int main()
{
    int x, y;
    int a, b;

    // Taking input from the user
    printf("Enter the first number: ");
    scanf("%d", &a);
    printf("Enter the second number: ");
    scanf("%d", &b);

    // Ensure positive integers
    if (a <= 0 || b <= 0)
    {
        printf("Please enter positive integers only.\n");
        return 1;
    }

    int g = gcdExtended(a, b, &x, &y);
    printf("gcd(%d, %d) = %d\n", a, b, g);
    printf("Coefficients: x = %d, y = %d\n", x, y);

    return 0;
}
