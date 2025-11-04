#include <stdio.h>

int main(void)
{
    int i = 1;
    do
    {
        int result = i * 13;
        printf("%d\n", result);
        i++;
    } while (i <= 10);
    return 0;
}