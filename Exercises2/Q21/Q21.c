#include <stdio.h>

int main(void)
{
    int i = 1;
    while (i <= 10)
    {
        int result = i * 13;
        printf("%d\n", result);
        i++;
    }
}