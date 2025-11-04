#include <stdio.h>
#include <string.h>

char *single[10] = { "zero", "one", "two", "three", "four",
                    "five", "six", "seven", "eight", "nine" };

char *teen[10] = { "ten", "eleven", "twelve", "thirteen", "fourteen",
                  "fifteen", "sixteen", "seventeen", "eighteen", "nineteen" };

char *ten[10] = { "", "", "twenty", "thirty", "forty",
                 "fifty", "sixty", "seventy", "eighty", "ninety" };

char *hundred[10] = { "", "one hundred", "two hundred", "three hundred", "four hundred",
                     "five hundred", "six hundred", "seven hundred", "eight hundred", "nine hundred" };                 

char *verbalise(int number)
{
    static char result[100];  // now persists after function returns
    result[0] = '\0';
    
    if (number > 999 || number < 0)
        return "Out of range";

    char *hundreds = hundred[number / 100];
    if (hundreds)
    {
        strcat(result, hundreds);
        number %= 100;
    }
    if (number >= 20)
    {
        char *tens = ten[number / 10];
        if (tens)
        {
            if (strlen(result) > 0) strcat(result, " and ");
            strcat(result, tens);
            number %= 10;
        }
    }
    else if (number >= 10)
    {
        char *teens = teen[number - 10];
        if (teens)
        {
            if (strlen(result) > 0) strcat(result, " ");
            strcat(result, teens);
            number = 0;
        }
    }
    if (number > 0)
    {
        char *singles = single[number];
        if (singles)
        {
            if (strlen(result) > 0) strcat(result, " ");
            strcat(result, singles);
        }
    }
    return result;
}

int main(void)
{
    int number;
    printf("Enter a number in the range 0 <= x <= 999: ");
    scanf("%d", &number);
    printf("You entered: %s\n", verbalise(number));
    return 0;
}