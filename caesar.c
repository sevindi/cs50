#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // Checks there is only one command line argument
    if (argc != 2)
    {
        printf("Usage: ./ceasar key\n");
        return 1;
    }
    else
    {
        // Convert input to int type
        int key = atoi(argv[1]);
        // Gets the plaintext
        string plainText = get_string("plaintext:");
        printf("ciphertext:");
        // Loop through the plaintext
        for (int i = 0, plainLength = strlen(plainText); i < plainLength; i++)
            // Cipher lower case according according to ascii value
            if islower(plainText[i])
            {
                printf("%c", (((plainText[i] + key - 97) % 26) + 97));
            }
            // Cipher upper case according according to ascii value
            else if isupper(plainText[i])
            {
                printf("%c", (((plainText[i] + key - 65) % 26) + 65));
            }
            // Print non-alphabetical values as it is
            else
            {
                printf("%c", plainText[i]);
            }
        printf("\n");
    }
}
