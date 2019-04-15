#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int shift(char c); // Turns letters to numbers accoring to their alphabetical place

int main(int argc, string argv[])
{
    // Checks there is only one command line argument
    if (argc != 2)
    {
        printf("Usage: ./vigenere keyword - Use only one word\n./");
        return 1;
    }
    // Checks only alphabetical characters used in commend line argument
    string key = argv[1]; 
    for (int i = 0, keyLength = strlen(key); i < keyLength; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Usage: ./vigenere keyword - Use only letters\n");
            return 1;
        }
    }
    int keyLength = strlen(key);
    string plainText = get_string("plaintext:");
    printf("ciphertext:");
    // Loop through the plaintext
    for (int j = 0, k = 0, plainLength = strlen(plainText); j < plainLength; j++)
    {
        // Get reference key for first letter and increment wrap to beginning of the key when it is over        
        int keyRef = shift(key[k % keyLength]);
                
        // Cipher lower case according according to ascii value
        if islower(plainText[j])
        {
            printf("%c", (((plainText[j] + keyRef - 97) % 26) + 97));
            k++;
        }
        // Cipher upper case according according to ascii value
        else if isupper(plainText[j])
        {
            printf("%c", (((plainText[j] + keyRef - 65) % 26) + 65));
            k++;
        }
        // Print non-alphabetical value as it is
        else
        {
            printf("%c", plainText[j]);
        }
    }
    printf("\n");
}

int shift(char c)
{
    int a;
    if (c > 64 && c < 91)
    {
        a = c - 65;
    }
    if (c > 96 && c < 123)
    {
        a = c - 97;
    }
    return a;
}
