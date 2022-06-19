// Implements a dictionary's functionality

#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Count how many word load
int count = 0;

// TODO: Choose number of buckets in hash table
const unsigned int N = (LENGTH + 1)  * 'z';

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO

    // Cursor
    node *cursor = table[hash(word)];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int sum = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        sum += tolower(word[i]);
    }
    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO

    // Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file != NULL)
    {
        {
            // Read one word from file one at a time
            char word[LENGTH + 1];
            while (fscanf(file, "%s", word) != EOF)
            {
                // Create a new node for each word
                node *n = malloc(sizeof(node));
                if (n != NULL)
                {
                    // Copy over word to new node
                    strcpy(n->word, word);
                    n->next = NULL;

                    // Hash word to obtain a hash value
                    // Insert node into hash table at that location
                    if (table[hash(word)] == NULL)
                    {
                        table[hash(word)] = n;
                    }
                    else
                    {
                        n->next = table[hash(word)];
                        table[hash(word)] = n;
                    }
                }
                count++;
            }
            fclose(file);
            return true;
        }
    }
    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO

    // Head, Cursor, Temp, order matters
    for (int i = 0; i < N; i++)
    {
        node *head = table[i];
        node *cursor = head;
        node *tmp = head;
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
