#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

unsigned int hash(const char *word);

int main()
{
    printf("%u\n", hash("LAND"));
}

unsigned int hash(const char *word)
    // FILE *file = fopen("dictionaries/small", "r");
    // {
    //     char word[46];
    //     while (fscanf(file, "%s", word) != EOF)
    //     {
    //         printf("%s\n", word);
    //     }
    // }
    // fclose(file);
{
    int hash = 0;
    int n;
    for (int i = 0; word[i] != '\0'; i++)
    {
        // Alphabet case
        if (isalpha(word[i]))
            n = word[i] - 'a' + 1;

        // Comma case
        else
            n = 27;

        hash = ((hash << 3) + n) % 101;
    }
    return hash;
}
