#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// Key length
#define KEY_LENGTH 26

bool only_alphas(string s);
char substitute(char c, string s);
bool no_duplicate(string s);

int main(int argc, string argv[])
{
    if (argc == 2 && only_alphas(argv[1]) && no_duplicate(argv[1]) && strlen(argv[1]) == KEY_LENGTH)
    {
        // Ask for input
        string plaintext = get_string("plaintext:  ");
        int l = strlen(plaintext);
        // Output
        printf("ciphertext: ");
        // Concatenate each encrypted letter
        for (int i = 0; i < l; i++)
        {
            char cipherchar = substitute(plaintext[i], argv[1]);
            printf("%c", cipherchar);
        }
        printf("\n");
    }
    else if (argc == 2 && only_alphas(argv[1]) && strlen(argv[1]) != KEY_LENGTH)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}

bool only_alphas(string s)
{
    for (int i = 0; i < KEY_LENGTH; i++)
    {
        if (isalpha(s[i]) == 0)
        {
            return false;
        }
    }
    return true;
}

bool no_duplicate(string s)
{
    char c;
    for (int i = 0; i < KEY_LENGTH; i++)
    {
        // Check containing each letter exactly once
        if (c == s[i])
        {
            return false;
        }
        c = s[i];
    }
    return true;
}

char substitute(char c, string s)
{
    if (isalpha(c))
    {
        // Prevent error (ASCII range from 0 to 127) (Unnecessary in this use case but a good habit)
        int index;
        if (isupper(c))
        {
            // Map to index of key (ASCII range from 65 to 90)
            index = c - 65;
            c = toupper(s[index]);
        }
        // Implicit lowercase
        else
        {
            // Map to index of key (ASCII range from 97 to 122)
            index = c - 97;
            c = tolower(s[index]);
        }
    }
    // Implicit nonletter
    return c;
}