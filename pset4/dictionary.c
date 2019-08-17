#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

#define H_SIZE 65536

// Define struct node
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;


// Declare dictionary word counter
int d_size = 0;

// Declare hashtable
node *hashtable[H_SIZE];

int hash(const char *word)
{
    unsigned int hash = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
        hash = (hash << 2) ^ word[i];
    return hash % H_SIZE;
}



// Returns true if word is in dictionary else false.

bool check(const char *word)
{
    int len = strlen(word);
    char l_word[len + 1];
    for (int i = 0; i < len; i++)
    {
        l_word[i] = tolower(word[i]);
    }
    l_word[len] = '\0';

    int bucket = hash(l_word);
    node *cursor = hashtable[bucket];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, l_word) != 0)
            cursor = cursor->next;
        else
            return true;
    }
    return false;
}

//Loads dictionary into memory. Returns true if successful else false.

bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        fprintf(stderr, "Couldn't open the dictionary %s.\n", dictionary);
        return false;
    }

    char b_word[LENGTH + 1];

    while (fscanf(dict, "%s", b_word) != EOF)
    {

        node *temp = malloc(sizeof(node));

        strncpy(temp->word, b_word, sizeof(b_word));


        int index = hash(b_word);


        if (hashtable[index] == NULL)
            hashtable[index] = temp;

        else
        {
            temp->next = hashtable[index];
            hashtable[index] = temp;
        }
        d_size ++;
    }
    fclose(dict);
    return true;
}

//Returns number of words in dictionary if loaded else 0 if not yet loaded.

unsigned int size(void)
{
    return d_size;
}

void wipe(node *head)
{
    if (head->next != NULL)
    {
        wipe(head->next);
    }
    free(head);
}


//Unloads dictionary from memory. Returns true if successful else false.

bool unload(void)
{
    for (int i = 0; i < H_SIZE; i++)
    {
        if (hashtable[i] != NULL)
        {
            wipe(hashtable[i]);
        }
    }
    return true;
}
