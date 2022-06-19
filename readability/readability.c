#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string s);
int count_words(string s);
int count_sentences(string s);

int main(void)
{
    // Get input text from user
    string text = get_string("Text: ");
    int w = count_words(text);
    int l = count_letters(text);
    int s = count_sentences(text);

    // Cast values to float before performing division when calculating L and S! Otherwise the result will be truncated
    float L = l * 100.00 / w;
    float S = s * 100.00 / w;

    // Round the resulting index number to the nearest int
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int count_words(string s)
{
    int l = strlen(s);

    // Assume that a sentence will not start or end with a space
    int c = 1;
    for (int i = 0; i < l; i++)
    {
        if (isspace(s[i]))
        {
            c++;
        }
    }
    return c;
}

int count_letters(string s)
{
    int l = strlen(s);
    int c = 0;
    for (int i = 0; i < l; i++)
    {
        if (isalpha(s[i]))
        {
            c++;
        }
    }
    return c;
}

int count_sentences(string s)
{
    int l = strlen(s);
    int c = 0;
    for (int i = 0; i < l; i++)
    {
        // Consider any sequence of characters that ends with a . or a ! or a ? to be a sentence
        if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            c++;
        }
    }
    return c;
}
