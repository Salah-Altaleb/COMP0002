#include <stdio.h>

char ZERO[5][9] = {
    " ****** ",
    " *    * ",
    " ****** ",
    " *    * ",
    " ****** "
};

char ONE[5][6] = {
    "  *  ",
    " **  ",
    "  *  ",
    "  *  ",
    " *** "
};

char TWO[5][9] = {
    " ****** ",
    "      * ",
    " ****** ",
    " *      ",
    " ****** "
};

char THREE[5][9] = {
    " ****** ",
    "      * ",
    " ****** ",
    "      * ",
    " ****** "
};

char FOUR[5][9] = {
    " *    * ",
    " *    * ",
    " ****** ",
    "      * ",
    "      * "
};

char FIVE[5][9] = {
    " ****** ",
    " *      ",
    " ****** ",
    "      * ",
    " ****** "
};

char SIX[5][9] = {
    " ****** ",
    " *      ",
    " ****** ",
    " *    * ",
    " ****** "
};

char SEVEN[5][9] = {
    " ****** ",
    "      * ",
    "      * ",
    "      * ",
    "      * "
};

char EIGHT[5][9] = {
    " ****** ",
    " *    * ",
    " ****** ",
    " *    * ",
    " ****** "
};

char NINE[5][9] = {
    " ****** ",
    " *    * ",
    " ****** ",
    "      * ",
    " ****** "
};

void big0(int line) { printf("%s ", ZERO[line - 1]); }
void big1(int line) { printf("%s ", ONE[line - 1]); }
void big2(int line) { printf("%s ", TWO[line - 1]); }
void big3(int line) { printf("%s ", THREE[line - 1]); }
void big4(int line) { printf("%s ", FOUR[line - 1]); }
void big5(int line) { printf("%s ", FIVE[line - 1]); }
void big6(int line) { printf("%s ", SIX[line - 1]); }
void big7(int line) { printf("%s ", SEVEN[line - 1]); }
void big8(int line) { printf("%s ", EIGHT[line - 1]); }
void big9(int line) { printf("%s ", NINE[line - 1]); }

void printBigNumber(int num) {
    int digits[10];
    int count = 0;

    // Extract digits (in reverse order)
    while (num > 0) {
        digits[count++] = num % 10;
        num /= 10;
    }

    // Print line by line (top to bottom)
    for (int line = 1; line <= 5; line++) {
        for (int i = count - 1; i >= 0; i--) {
            switch (digits[i]) {
                case 1: big1(line); break;
                case 2: big2(line); break;
                case 3: big3(line); break;
                case 4: big4(line); break;
                case 5: big5(line); break;
                case 6: big6(line); break;
                case 7: big7(line); break;
                case 8: big8(line); break;
                case 9: big9(line); break;
                case 0: big0(line); break;
                default: printf("      "); break; // space for unsupported digits
            }
        }
        printf("\n");
    }
}

int main(void) {
    int num;
    printf("Enter a number (1 - 9 digits): ");
    scanf("%d", &num);

    printBigNumber(num);
    return 0;
}