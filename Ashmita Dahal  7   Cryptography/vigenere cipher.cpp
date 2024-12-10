#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to generate the key in a cyclic manner
void generateKey(const char *str, const char *keyword, char *key)
{
    int x = strlen(str);
    int keywordLength = strlen(keyword);

    for (int i = 0; i < x; i++)
    {
        key[i] = keyword[i % keywordLength];
    }
    key[x] = '\0';
}

// Function to return the encrypted text
void cipherText(const char *str, const char *key, char *cipher_text)
{
    int n = strlen(str);

    for (int i = 0; i < n; i++)
    {
        // Convert to uppercase
        char x = (toupper(str[i]) - 'A' + toupper(key[i]) - 'A') % 26;

        // Convert into alphabets (ASCII)
        x += 'A';

        cipher_text[i] = x;
    }
    cipher_text[n] = '\0';
}

// Function to decrypt the encrypted text and return the original text
void originalText(const char *cipher_text, const char *key, char *orig_text)
{
    int n = strlen(cipher_text);

    for (int i = 0; i < n; i++)
    {
        // Convert to uppercase
        char x = (cipher_text[i] - key[i] + 26) % 26;

        // Convert into alphabets (ASCII)
        x += 'A';
        orig_text[i] = x;
    }
    orig_text[n] = '\0';
}

int main()
{
    char str[100], keyword[100], key[100], cipher_text[100], orig_text[100];

    while (1)
    {
        printf("\nMenu:\n");
        printf("1. Encrypt Text\n");
        printf("2. Decrypt Text\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);

        if (choice == 1)
        {
            printf("Enter the plain text: ");
            scanf(" %[^\n]", str);
            printf("Enter the keyword (string): ");
            scanf("%s", keyword);

            generateKey(str, keyword, key);
            cipherText(str, key, cipher_text);

            printf("Encrypted Text: %s\n", cipher_text);
        }
        else if (choice == 2)
        {
            printf("Enter the cipher text: ");
            scanf(" %[^\n]", cipher_text);
            printf("Enter the keyword (string): ");
            scanf("%s", keyword);

            generateKey(cipher_text, keyword, key);
            originalText(cipher_text, key, orig_text);

            printf("Decrypted Text: %s\n", orig_text);
        }
        else if (choice == 3)
            break;
        else
            printf("Invalid choice. Please enter a valid option.\n");
    }

    return 0;
}
