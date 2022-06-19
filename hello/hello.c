#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Ask user's name
    string answer = get_string("What's your name? ");
    printf("hello, %s\n", answer);
}