#include <stdio.h>

int get_power_by_loop(int base, int exponent) {
    int result = 1;
    for (int i = 0; i < exponent; i++) 
    {
        result *= base;
    }
    return result;
}

int get_power_by_recursion(int base, int exponent) {
    if (exponent == 0) 
    {
        return 1;
    } 
    else 
    {
        return base * get_power_by_recursion(base, exponent - 1);
    }
}

int main(void) 
{
    int base, exponent;

    printf("Enter base and exponent: ");
    scanf("%d %d", &base, &exponent);

    int result_loop = get_power_by_loop(base, exponent);
    int result_recursion = get_power_by_recursion(base, exponent);

    printf("Result using loop: %d\n", result_loop);
    printf("Result using recursion: %d\n", result_recursion);

    return 0;
}