#include <stdio.h>
#include <stdbool.h>

int factorial(int n) {
    if (n < 0) {
        return -1;
    }
    if (n == 0 || n == 1) {
        return 1;
    }
    return n * factorial(n - 1); // Recursive case
}

bool isStrongNumber(int number) 
{
    int originalNumber = number;
    int sum = 0;

    while (number > 0) 
    {
        int digit = number % 10;
        int fact = factorial(digit);
        if (fact == -1) 
        {
            return false;
        }
        sum += fact;
        number /= 10;
    }

    return sum == originalNumber;
}

int main() 
{
    int start,end;
    printf("Enter Start and End values: ");
    scanf("%d %d", &start, &end);

    if (start < 0) 
    {
        printf("Please enter a non-negative integer.\n");
        return 1;
    }

    if (end < start) 
    {
        printf("End value should be greater than or equal to Start value.\n");
        return 1;
    }

    int strongNumbers[20];
    int count = 0;

    for (int number = start; number <= end; number++) 
    {
        if (isStrongNumber(number)) 
        {
            strongNumbers[count++] = number;
        }
    }
    printf("Strong numbers between %d and %d are:\n", start, end);
    for (int j = 0; j < count; j++) 
    {
        printf("%d ", strongNumbers[j]);
    }

    return 0;
}