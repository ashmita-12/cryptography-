#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 30

void toLowerCase(char[], int);
int removeSpaces(char *, int);
void generateKeyTable(char[], int, char[][5]);
void search(char[][5], char, char, int[]);
int mod5encrypt(int);
int mod5decrypt(int);
int prepare(char[], int);
void encrypt(char[], char[][5], int);
void encryptByPlayfairCipher(char[], char[]);
void decrypt(char[], char[][5], int);
void decryptByPlayfairCipher(char[], char[]);
void displayKeyMatrix(char[][5]);

int main()
{
    char str[SIZE], key[SIZE];
    char keyT[5][5];

    int choice;
    do
    {
        printf("Menu:\n");
        printf("1. Encrypt\n");
        printf("2. Decrypt\n");
        printf("3. Exit\n");
        printf("Enter your choice (1/2/3): ");
        scanf("%d", &choice);
        getchar(); // To consume the newline character after the choice

        switch (choice)
        {
        case 1:
            printf("Enter key text: ");
            fgets(key, SIZE, stdin);
            key[strcspn(key, "\n")] = '\0'; // Remove the trailing newline character

            printf("Enter plain text: ");
            fgets(str, SIZE, stdin);
            str[strcspn(str, "\n")] = '\0'; // Remove the trailing newline character

            // Generate and display the key matrix
            generateKeyTable(key, strlen(key), keyT);
            displayKeyMatrix(keyT);

            // Encrypt and display the cipher text
            encryptByPlayfairCipher(str, key);
            for (int i = 0; str[i]; i++)
            {
                str[i] = toupper(str[i]);
            }
            printf("\nCipher text: %s\n", str);
            break;

        case 2:
            printf("Enter key text: ");
            fgets(key, SIZE, stdin);
            key[strcspn(key, "\n")] = '\0'; // Remove the trailing newline character

            printf("Enter cipher text: ");
            fgets(str, SIZE, stdin);
            str[strcspn(str, "\n")] = '\0'; // Remove the trailing newline character

            // Generate and display the key matrix
            generateKeyTable(key, strlen(key), keyT);
            displayKeyMatrix(keyT);

            // Decrypt and display the plain text
            decryptByPlayfairCipher(str, key);
            for (int i = 0; str[i]; i++)
            {
                str[i] = toupper(str[i]);
            }
            printf("\nDecrypted text: %s\n", str);
            break;

        case 3:
            printf("Exiting program...\n");
            break;

        default:
            printf("Invalid choice. Please enter 1, 2, or 3.\n");
            break;
        }
    } while (choice != 3);

    return 0;
}

// Function to convert the string to lowercase
void toLowerCase(char plain[], int ps)
{
    for (int i = 0; i < ps; i++)
    {
        if (plain[i] > 64 && plain[i] < 91)
            plain[i] += 32;
    }
}

// Function to remove all spaces in a string
int removeSpaces(char *plain, int ps)
{
    int count = 0;
    for (int i = 0; i < ps; i++)
        if (plain[i] != ' ')
            plain[count++] = plain[i];
    plain[count] = '\0';
    return count;
}

// Function to generate the 5x5 key square
void generateKeyTable(char key[], int ks, char keyT[5][5])
{
    int dicty[26] = {0};

    for (int i = 0; i < ks; i++)
    {
        if (key[i] != 'j')
            dicty[key[i] - 97] = 2;
    }

    dicty['j' - 97] = 1;

    int i = 0, j = 0;
    for (int k = 0; k < ks; k++)
    {
        if (dicty[key[k] - 97] == 2)
        {
            dicty[key[k] - 97] -= 1;
            keyT[i][j] = key[k];
            j++;
            if (j == 5)
            {
                i++;
                j = 0;
            }
        }
    }

    for (int k = 0; k < 26; k++)
    {
        if (dicty[k] == 0)
        {
            keyT[i][j] = (char)(k + 97);
            j++;
            if (j == 5)
            {
                i++;
                j = 0;
            }
        }
    }
}

// Function to search for the characters of a digraph in the key square and return their position
void search(char keyT[5][5], char a, char b, int arr[])
{
    if (a == 'j')
        a = 'i';
    else if (b == 'j')
        b = 'i';

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (keyT[i][j] == a)
            {
                arr[0] = i;
                arr[1] = j;
            }
            else if (keyT[i][j] == b)
            {
                arr[2] = i;
                arr[3] = j;
            }
        }
    }
}

// Function to find the modulus with 5
int mod5encrypt(int a)
{
    return (a % 5);
}

int mod5decrypt(int a)
{
    if (a < 0)
        a += 5;
    return (a % 5);
}

// Function to make the plain text length to be even
int prepare(char str[], int ptrs)
{
    if (ptrs % 2 != 0)
    {
        str[ptrs++] = 'z';
        str[ptrs] = '\0';
    }
    return ptrs;
}

// Function for performing the encryption
void encrypt(char str[], char keyT[5][5], int ps)
{
    int a[4];

    for (int i = 0; i < ps; i += 2)
    {
        search(keyT, str[i], str[i + 1], a);

        if (a[0] == a[2])
        {
            str[i] = keyT[a[0]][mod5encrypt(a[1] + 1)];
            str[i + 1] = keyT[a[0]][mod5encrypt(a[3] + 1)];
        }
        else if (a[1] == a[3])
        {
            str[i] = keyT[mod5encrypt(a[0] + 1)][a[1]];
            str[i + 1] = keyT[mod5encrypt(a[2] + 1)][a[1]];
        }
        else
        {
            str[i] = keyT[a[0]][a[3]];
            str[i + 1] = keyT[a[2]][a[1]];
        }
    }
}

// Function to encrypt using Playfair Cipher
void encryptByPlayfairCipher(char str[], char key[])
{
    int ks = strlen(key);
    ks = removeSpaces(key, ks);
    toLowerCase(key, ks);

    int ps = strlen(str);
    toLowerCase(str, ps);
    ps = removeSpaces(str, ps);

    ps = prepare(str, ps);

    char keyT[5][5];
    generateKeyTable(key, ks, keyT);

    encrypt(str, keyT, ps);
}

// Function to decrypt
void decrypt(char str[], char keyT[5][5], int ps)
{
    int a[4];
    for (int i = 0; i < ps; i += 2)
    {
        search(keyT, str[i], str[i + 1], a);
        if (a[0] == a[2])
        {
            str[i] = keyT[a[0]][mod5decrypt(a[1] - 1)];
            str[i + 1] = keyT[a[0]][mod5decrypt(a[3] - 1)];
        }
        else if (a[1] == a[3])
        {
            str[i] = keyT[mod5decrypt(a[0] - 1)][a[1]];
            str[i + 1] = keyT[mod5decrypt(a[2] - 1)][a[1]];
        }
        else
        {
            str[i] = keyT[a[0]][a[3]];
            str[i + 1] = keyT[a[2]][a[1]];
        }
    }
}

// Function to call decrypt
void decryptByPlayfairCipher(char str[], char key[])
{
    int ks = strlen(key);
    ks = removeSpaces(key, ks);
    toLowerCase(key, ks);

    int ps = strlen(str);
    toLowerCase(str, ps);
    ps = removeSpaces(str, ps);

    char keyT[5][5];
    generateKeyTable(key, ks, keyT);

    decrypt(str, keyT, ps);
}

// Function to display the key matrix
void displayKeyMatrix(char keyT[5][5])
{
    printf("Key Matrix:\n");
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            char capitalized = toupper(keyT[i][j]);
            printf("%c ", capitalized);
        }
        printf("\n");
    }
}
