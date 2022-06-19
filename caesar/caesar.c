#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool only_digits(string s);
char rotate(char c, int i);

int main(int argc, string argv[])
{
    if (argc == 2 && only_digits(argv[1]))
    {
        int pos;
        // Convert string to int
        int key = atoi(argv[1]);
        // Ask for input
        string plaintext = get_string("plaintext:  ");
        // Determine how many moving positions
        if (key > 26)
        {
            pos = key % 26;
        }
        else
        {
            pos = key;
        }
        int l = strlen(plaintext);
        // Output
        printf("ciphertext: ");
        // Concatenate each encrypted letter
        for (int i = 0; i < l; i++)
        {
            char cipherchar = rotate(plaintext[i], pos);
            printf("%c", cipherchar);
        }
        printf("\n");
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}


bool only_digits(string s)
{
    int l = strlen(s);
    for (int i = 0; i < l; i++)
    {
        if (isdigit(s[i]) == 0)
        {
            return false;
        }
    }
    return true;
}

char rotate(char c, int i)
{
    if (isalpha(c))
    {
        // Prevent error (ASCII range from 0 to 127)
        int p;
        if (isupper(c))
        {
            p = c + i;
            // Wrapping around from Z to A
            if (p > 90)
            {
                p -= 26;
            }
        }
        // Implicit lowercase
        else
        {
            p = c + i;
            // Wrapping around from z to a
            if (p > 122)
            {
                p -= 26;
            }
        }
        // Encrypted letter
        return p;
    }
    // Implicit nonletter
    return c;
}