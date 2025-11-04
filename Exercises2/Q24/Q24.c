#include <stdio.h>

int main(void)
{
    int rows = 4;
    int cols = 5;
    for (int i = 0; i < rows; i++) {
        if (i == 0 || i == rows - 1)
        {
            for (int j = 0; j < cols; j++)
            {
                printf("*");
            }
        }
        else
        {
            for (int j = 0; j < cols; j++)
            {
                if (j == 0 || j == cols - 1)
                    printf("*");
                else
                    printf(" ");
            }
        }
        printf("\n");
    }
}