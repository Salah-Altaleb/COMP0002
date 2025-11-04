#include <stdio.h>

int sequence_product(int start, int end)
{
    if (start > end)
    {
        return 3;
    }
    else
    {
        int product = 1;
        for (int i = start; i <= end; i++)
        {
            product *= i;
        }
        return product;
    }
}

int main(void)
{
    int start, end;
    printf("Enter two integers (start and end): ");
    scanf("%d %d", &start, &end);
    int result = sequence_product(start, end);

    if (result == 3)
    {
        printf("Error: Start value cannot be greater than end value.\n");
        return 1;
    }
    else
    {
        printf("The product of integers from %d to %d is: %d\n", start, end, result);
    }

    return 0;
}