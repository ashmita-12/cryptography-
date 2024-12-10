#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEXT_LENGTH 1000
#define KEY 3

void encrypt(char *plaintext, char *ciphertext);
void decrypt(char *ciphertext, char *plaintext);

int main()
{
    int choice;
    char plaintext[MAX_TEXT_LENGTH], ciphertext[MAX_TEXT_LENGTH];

    do
    {
        printf("Menu:\n");
        printf("1. Encrypt\n");
        printf("2. Decrypt\n");
        printf("3. Exit\n");
        printf("Enter your choice (1/2/3): ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice)
        {
        case 1:
            printf("Enter the plaintext: ");
            fgets(plaintext, MAX_TEXT_LENGTH, stdin);
            plaintext[strcspn(plaintext, "\n")] = 0;

            encrypt(plaintext, ciphertext);
            printf("Encrypted Text: %s\n\n", ciphertext);
            break;

        case 2:
            printf("Enter the ciphertext: ");
            fgets(ciphertext, MAX_TEXT_LENGTH, stdin);
            ciphertext[strcspn(ciphertext, "\n")] = 0;

            decrypt(ciphertext, plaintext);
            printf("Decrypted Text: %s\n\n", plaintext);
            break;

        case 3:
            printf("Exiting program...\n");
            printf("NAME: Nutan Gyawali \n Roll number: 28387/078");
            break;

        default:
            printf("Invalid choice. Please enter 1, 2, or 3.\n");
            printf("NAME: Nutan Gyawali \n Roll number: 28387/078");
            break;
        }
    } while (choice != 3);

    return 0;
}
void encrypt(char *plaintext, char *ciphertext)
{
    int i;
    for (i = 0; plaintext[i] != '\0'; i++)
    {
        if (isalpha(plaintext[i]))
        {
            char base = islower(plaintext[i]) ? 'a' : 'A';
            ciphertext[i] = ((plaintext[i] - base + KEY) % 26) + base;
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[i] = '\0'; 
}
void decrypt(char *ciphertext, char *plaintext)
{
    int i;
    for (i = 0; ciphertext[i] != '\0'; i++)
    {
        if (isalpha(ciphertext[i]))
        {
            char base = islower(ciphertext[i]) ? 'a' : 'A';
            plaintext[i] = ((ciphertext[i] - base - KEY + 26) % 26) + base;
        }
        else
        {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[i] = '\0'; 
}
