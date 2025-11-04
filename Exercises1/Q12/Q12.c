// Written by Salah, 4/10/2025
// This program displays my name.

#include <stdio.h>
#include <string.h>

int main(void)
{
    char deptName[] = "Dept. of Computer Science";
    char address1[] = "66 - 72 Gower Street London WC1E 6EA";
    printf("The %s is based in %s\n", deptName, address1);
    int index = strlen(deptName) - 1;
    while (index > -1)
    {
        printf("%c", deptName[index]);
        index = index - 1;
    }
    printf("\n");
    return 0;
}