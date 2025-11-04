#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

bool isPrime(long number) 
{
    if (number <= 1) 
    {
        return false;
    }

    int divisorCount = 0;
    for (int j = 2; j * j <= number; j++) {  // check divisibility up to sqrt(i)
        if (number % j == 0) {
            divisorCount++;
            break;
        }
    }
    
    if (divisorCount == 0) 
    {
        return true;
    } 
    else 
    {
        return false;
    }

    printf("\n");
}

int main(void) {
    
    int result;
    char input[50];
    
    while (1) 
    {
        printf("Enter a number (or 'Stop' to exit): ");
        scanf("%s", input);

        if (strcmp(input, "Stop") == 0)
            break;

        char *end;
        long number = strtol(input, &end, 10);

        printf("End char: '%c'\n", *end == '\0' ? '0' : *end);


        if (*end != '\0') {
            printf("Invalid input! Please enter a number.\n");
            continue;
        }

        if (isPrime(number))
            printf("%ld is Prime\n", number);
        else
            printf("%ld is Not Prime\n", number);
    }

}
