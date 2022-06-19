#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Validate user input
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    // For each row
    for (int i = 0; i < n; i++)
    {
        // For each column (left-aligned)
        // {
        //     for (int j = 0; j < n; j++)
        //     {
        //         if (i - j >= 0)
        //             printf("#");
        //     }
        //     printf("\n");
        // }
        // For each column (right-aligned)
        {
            for (int j = 0; j < n; j++)
            {
                if (i + j >= n - 1)
                {
                    printf("#");
                }
                else
                {
                    printf(" ");
                }
            }
            printf("\n");
        }
    }
}