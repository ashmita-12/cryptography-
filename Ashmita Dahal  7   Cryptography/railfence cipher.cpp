#include <stdio.h>
#include <string.h>

void encryptMsg(char *msg, int key, char *cipher_text);
void decryptMsg(char *enMsg, int key, char *decrypted_text);

int main()
{
    int choice, key;
    char plain_text[100], cipher_text[100], decrypted_text[100];
    do
    {
        printf("\nMenu:\n");
        printf("1. Encrypt\n");
        printf("2. Decrypt\n");
        printf("3. Exit\n");
        printf("Enter your choice (1/2/3): ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter the plain text: ");
            getchar(); // consume newline left by previous input
            fgets(plain_text, sizeof(plain_text), stdin);
            plain_text[strcspn(plain_text, "\n")] = 0; // remove newline character
            printf("Enter the key: ");
            scanf("%d", &key);
            encryptMsg(plain_text, key, cipher_text);
            printf("Encrypted Text: %s\n", cipher_text);
            break;

        case 2:
            printf("Enter the cipher text: ");
            getchar(); // consume newline left by previous input
            fgets(cipher_text, sizeof(cipher_text), stdin);
            cipher_text[strcspn(cipher_text, "\n")] = 0; // remove newline character
            printf("Enter the key: ");
            scanf("%d", &key);
            decryptMsg(cipher_text, key, decrypted_text);
            printf("Decrypted Text: %s\n", decrypted_text);
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

// function to encrypt a message
void encryptMsg(char *msg, int key, char *cipher_text)
{
    int msgLen = strlen(msg);
    int i, j, k = -1, row = 0, col = 0;
    char railMatrix[key][msgLen];
    memset(cipher_text, 0, sizeof(char) * msgLen); // clear the output buffer

    // Initialize the rail matrix with newline characters
    for (i = 0; i < key; ++i)
        for (j = 0; j < msgLen; ++j)
            railMatrix[i][j] = '\n';

    // Populate the rail matrix with characters from the message
    for (i = 0; i < msgLen; ++i)
    {
        railMatrix[row][col++] = msg[i];
        if (row == 0 || row == key - 1)
            k = k * (-1);
        row = row + k;
    }

    // Read the matrix to construct the cipher text
    int index = 0;
    for (i = 0; i < key; ++i)
    {
        for (j = 0; j < msgLen; ++j)
        {
            if (railMatrix[i][j] != '\n')
            {
                cipher_text[index++] = railMatrix[i][j];
            }
        }
    }
    cipher_text[index] = '\0';
}

// function to decrypt a message
void decryptMsg(char *enMsg, int key, char *decrypted_text)
{
    int msgLen = strlen(enMsg);
    int i, j, k = -1, row = 0, col = 0, m = 0;
    char railMatrix[key][msgLen];
    memset(decrypted_text, 0, sizeof(char) * msgLen); // clear the output buffer

    // Initialize the rail matrix with newline characters
    for (i = 0; i < key; ++i)
        for (j = 0; j < msgLen; ++j)
            railMatrix[i][j] = '\n';

    // Mark positions in the matrix with '*'
    for (i = 0; i < msgLen; ++i)
    {
        railMatrix[row][col++] = '*';
        if (row == 0 || row == key - 1)
            k = k * (-1);
        row = row + k;
    }

    // Fill the rail matrix with the cipher text
    for (i = 0; i < key; ++i)
        for (j = 0; j < msgLen; ++j)
            if (railMatrix[i][j] == '*')
                railMatrix[i][j] = enMsg[m++];

    // Read the matrix to construct the decrypted text
    row = col = 0;
    k = -1;
    int index = 0;
    for (i = 0; i < msgLen; ++i)
    {
        decrypted_text[index++] = railMatrix[row][col++];
        if (row == 0 || row == key - 1)
        {
            k = k * (-1);
        }
        row = row + k;
    }
    decrypted_text[index] = '\0';
}
