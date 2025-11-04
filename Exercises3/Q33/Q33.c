#include <stdio.h>
#include <string.h>

int is_palindrome(long number)
{
    char buffer[50];
    sprintf(buffer, "%ld", number);

    int digits = strlen(number < 0 ? buffer + 1 : buffer);

    for (int i = 0; i < digits / 2; i++)
    {
        if (buffer[i] == buffer[digits - i - 1])
        {
            continue;
        }
        else
        {
            return 1;
        }
    }
    return 0;
}

int main(void)
{
    long number;
    printf("Enter an integer: ");
    scanf("%ld", &number);

    if (is_palindrome(number) == 0)
    {
        printf("%ld is a palindrome.\n", number);
    }
    else
    {
        printf("%ld is not a palindrome.\n", number);
    }
    return 0;
}