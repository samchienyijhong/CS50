#include <cs50.h>
#include <stdio.h>

bool checksum(long n);
void checklenth(long n);

int main(void)
{
    long n;
    do
    {
        n = get_long("Number: ");
    }

    // Validate user input
    while (n < 0);
    if (checksum(n))
    {
        checklenth(n);
    }
    else
    {
        printf("INVALID\n");
    }
}

bool checksum(long n)
{
    // Digit
    int d = 1;

    // Divisor
    long i = 10;

    // Target
    long r = 0;

    // Result
    int f = 0;

    // Condition
    long k = n;
    
    while (k != 0)
    {
        r = (n % i) / (i / 10);
        i *= 10;
        k /= 10;
        d++;
        if (d % 2 != 0)
        {
            r *= 2;
        }
        if (r >= 10)
        {
            f += r % 10;
            f += r / 10;
        }
        else
        {
            f += r;
        }
    }
    return f % 10 == 0;
}

void checklenth(long n)
{
    // 34 followed by 13 zeros to 35 followed by 13 zeros OR 37 followed by 13 zeros to 38 followed by 13 zeros
    if ((n >= 34e13 && n < 35e13) || (n >= 37e13 && n < 38e13))
    {
        printf("AMEX\n");
    }

    // 51 followed by 14 zeros to 57 followed by 14 zeros
    else if (n >= 51e14 && n < 56e14)
    {
        printf("MASTERCARD\n");
    }

    // 4 followed by 12 zeros to 4 followed by 12 zeros OR 4 followed by 15 zeros to 5 followed by 15 zeros
    else if ((n >= 4e12 && n < 5e12) || (n >= 4e15 && n < 5e15))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
