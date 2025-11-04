#include <stdio.h>

int main(void) 
{
    int rows = 7;
    int cols = 8;

    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            if (i == 0 || i == rows - 1) 
            {
                printf("*");
            }
            else if (j == 0 || j == cols - 1) 
            {
                printf("*");
            }
            else 
            {
                if ((i == 2 || i == 4) && (j >= 2 && j <= 5)) 
                {
                    printf("#");
                }
                else if (i == 3 && (j == 2 || j == 5)) 
                {
                    printf("#");
                }
                else 
                {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }

    return 0;
}
