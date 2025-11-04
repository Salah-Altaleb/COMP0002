#include <stdio.h>

int main(void) {
    int rows = 8;   // total rows
    int cols = 7;   // total columns

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // First row: all *
            if (i == 0) {
                printf("*");
            }
            // Last row: all #
            else if (i == rows - 1) {
                printf("#");
            }
            // Last column: always *
            else if (j == cols - 1) {
                printf("*");
            }
            // Diagonal #: column = row - 1
            else if (i > 0 && j == i - 1) {
                printf("#");
            }
            // The star just after the diagonal #: column = i
            else if (i > 0 && j == i) {
                printf("*");
            }
            // First column (if not filled yet)
            else if (j == 0) {
                printf("#");
            }
            // All other positions: space
            else {
                printf(" ");
            }
        }
        printf("\n");
    }

    return 0;
}
