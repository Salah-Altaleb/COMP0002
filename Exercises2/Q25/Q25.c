#include <stdio.h>

int main(void) {
    int rows = 6;

    for (int i = 0; i < rows; i++) {
        for (int space = 0; space < i; space++) {
            printf(" ");
        }

        for (int star = 0; star < rows - i; star++) {
            printf("*");
        }

        printf("\n");
    }

    return 0;
}
