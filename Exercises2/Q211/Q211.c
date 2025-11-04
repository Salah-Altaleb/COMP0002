#include <stdio.h>
#include <stdbool.h>

// Function a: Print squares of numbers from 1 to 100
void printSquares1to100() {
    printf("Squares of numbers from 1 to 100:\n");
    for (int i = 1; i <= 100; i++) {
        printf("%d^2 = %d\n", i, i * i);
    }
    printf("\n");
}

// Function b: Print squares of even numbers between 1 and 101
void printSquaresEven() {
    printf("Squares of even numbers between 1 and 101:\n");
    for (int i = 2; i <= 100; i += 2) {
        printf("%d^2 = %d\n", i, i * i);
    }
    printf("\n");
}

// Function c: Print prime numbers between 1 and 100
void printPrimes() {
    printf("Prime numbers between 1 and 100:\n");
    for (int i = 2; i <= 100; i++) {
        bool isPrime = true;
        for (int j = 2; j * j <= i; j++) {  // check divisibility up to sqrt(i)
            if (i % j == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main(void) {
    //printSquares1to100();
    //printSquaresEven();
    printPrimes();
    return 0;
}
