#include <stdio.h>

int main(void) 
{
    int n = 5;

    for (int i = 1; i <= n; i++) 
    {
        for (int j = 1; j <= i; j++) 
        {
            if (j == 1 || j == i) 
            {
                printf("*");
            } 
            else 
            {
                printf(" ");
            }
        }
        printf("\n");
    }

    for (int i = n - 1; i >= 1; i--) 
    {
        for (int j = 1; j <= i; j++) 
        {
            if (j == 1 || j == i) 
            {
                printf("*");
            } 
            else 
            {
                printf(" ");
            }
        }
        printf("\n");
    }

    return 0;
}
