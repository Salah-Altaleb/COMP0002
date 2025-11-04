#include <stdio.h>

int main(void) {
    int rows = 5; 

    for (int i = 0; i < rows; i++) 
    {
        for (int space = 0; space < i; space++) 
        {
            printf(" ");
        }

        for (int star = 0; star < rows; star++) 
        {
            printf("*");
        }

        printf("\n");
    }

    for (int i = rows - 2; i >= 0; i--) 
    {
        for (int space = 0; space < i; space++) 
        {
            printf(" ");
        }

        for (int star = 0; star < rows; star++) 
        {
            printf("*");
        }

        printf("\n");
    }

    return 0;
}
