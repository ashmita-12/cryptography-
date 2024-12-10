#include <stdio.h>

// Using Euclidean Algorithm (Repeated Subtraction)
int main()
{
    int n1, n2, gcd = 1;

    // Taking input from the user
    printf("Enter the first number: ");
    scanf("%d", &n1);
    printf("Enter the second number: ");
    scanf("%d", &n2);

    // Ensure positive integers
    if (n1 <= 0 || n2 <= 0)
    {
        printf("Please enter positive integers only.\n");
        return 1;
    }

    // Using the Euclidean Algorithm (Repeated Subtraction)
    while (n1 != n2)
    {
        if (n1 > n2)
            n1 -= n2;
        else
            n2 -= n1;
    }

    printf("The GCD: %d\n", n1);

    return 0;
}
