#include <stdio.h>
#include <stdbool.h>

void printTwinPrimes(int start, int end) 
{
    int primes[1000];
    int count = 0;

    if (start < 2) 
    {
        start = 2;
    }

    for (int i = start; i <= end; i++) {
        bool isPrime = true;
        for (int j = 2; j * j <= i; j++) 
        {
            if (i % j == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) 
        {
            primes[count++] = i;
        }
    }

    printf("Twin Primes between %d and %d are:\n", start, end);
    for (int k = 0; k < count; k++) 
    {
        if (primes[k + 1] - primes[k] <= 2) 
        {
            printf("(%d, %d) ", primes[k], primes[k + 1]);
        }
    }

    printf("\n");
}

int main(void) 
{
    int start, end;
    printf("Enter Start and End values:\n");
    scanf("%d %d", &start, &end);
    printTwinPrimes(start, end);
    return 0;
}
