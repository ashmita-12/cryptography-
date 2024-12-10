#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEXT_LENGTH 1000

int getKey();
void encrypt(char *plaintext, char *ciphertext, int key);
void decrypt(char *ciphertext, char *plaintext, int key);

int main()
{
    int choice;
    int key;
    char plaintext[MAX_TEXT_LENGTH], ciphertext[MAX_TEXT_LENGTH];

    do
    {
        printf("Menu:\n");
        printf("1. Encrypt\n");
        printf("2. Decrypt\n");
        printf("3. Exit\n");
        printf("Enter your choice (1/2/3): ");
        scanf("%d", &choice);
        getchar(); // to consume the newline character after scanf

        switch (choice)
        {
        case 1:
            printf("Enter the plaintext: ");
            fgets(plaintext, MAX_TEXT_LENGTH, stdin);
            // Remove trailing newline character from fgets
            plaintext[strcspn(plaintext, "\n")] = 0;

            printf("Enter the key (an integer between 0 to 25): ");
            key = getKey();

            encrypt(plaintext, ciphertext, key);
            printf("Encrypted Text: %s\n\n", ciphertext);

            break;

        case 2:
            printf("Enter the ciphertext: ");
            fgets(ciphertext, MAX_TEXT_LENGTH, stdin);
            // Remove trailing newline character from fgets
            ciphertext[strcspn(ciphertext, "\n")] = 0;

            printf("Enter the key (an integer between 0 to 25): ");
            key = getKey();

            decrypt(ciphertext, plaintext, key);
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


int getKey()
{
    int key;
    scanf("%d", &key);
    while (key < 0 || key > 25)
    {
        printf("Invalid key. Enter again: ");
        scanf("%d", &key);
    }

    return key;
}
void encrypt(char *plaintext, char *ciphertext, int key)
{
    int i;
    for (i = 0; plaintext[i] != '\0'; i++)
    {
        if (isalpha(plaintext[i]))
        {
            char base = islower(plaintext[i]) ? 'a' : 'A';
            ciphertext[i] = ((plaintext[i] - base + key) % 26) + base;
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[i] = '\0'; 
}
void decrypt(char *ciphertext, char *plaintext, int key)
{
    encrypt(ciphertext, plaintext, 26 - key); 
}
