#include <stdio.h>
#include <math.h>

int get_perimeter(int side1, int side2, int side3)
{
    return side1 + side2 + side3;
}

int get_semiperimeter(int side1, int side2, int side3)
{
    return get_perimeter(side1, side2, side3) / 2;
}

int get_area(int side1, int side2, int side3)
{
    int s = get_semiperimeter(side1, side2, side3);
    return sqrt(s * (s - side1) * (s - side2) * (s - side3));
}

int main()
{
    int side1, side2, side3;
    printf("Enter the lengths of the three sides of the triangle: ");
    scanf("%d %d %d", &side1, &side2, &side3);

    int perimeter = get_perimeter(side1, side2, side3);
    int semiperimeter = get_semiperimeter(side1, side2, side3);
    int area = get_area(side1, side2, side3);

    printf("Perimeter: %d\n", perimeter);
    printf("Semiperimeter: %d\n", semiperimeter);
    printf("Area: %d\n", area);

    return 0;
}