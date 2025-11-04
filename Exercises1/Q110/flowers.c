#include "graphics.h"

int main(void) {
    // Flower 1: 4 petals (left side)
    int x1 = 100;
    int y1 = 150;

    // Top
    setColour(cyan);
    fillArc(x1 + 2, y1 - 30, 25, 40, 0, 360);

    // Bottom
    setColour(red);
    fillArc(x1 + 2, y1 + 15, 25, 40, 0, 360);

    // Left
    setColour(green);
    fillArc(x1 - 30, y1, 40, 25, 0, 360);

    // Right
    setColour(gray);
    fillArc(x1 + 20, y1, 40, 25, 0, 360);

    // Centre
    setColour(yellow);
    fillArc(x1, y1, 30, 30, 0, 360);


    // Flower 2: 8 petals (right side)
    int x3 = 400;
    int y3 = 170;

    // Top
    setColour(black);
    fillArc(x3 + 2, y3 - 30, 25, 40, 0, 360);

    // Bottom
    setColour(gray);
    fillArc(x3 + 2, y3 + 15, 25, 40, 0, 360);

    // Left
    setColour(red);
    fillArc(x3 - 30, y3, 40, 25, 0, 360);

    // Right
    setColour(cyan);
    fillArc(x3 + 20, y3, 40, 25, 0, 360);

    // Upper-left diagonal
    setColour(blue);
    fillArc(x3 - 14, y3 - 14, 24, 24, 0, 360);

    // Upper-right diagonal
    setColour(pink);
    fillArc(x3 + 20, y3 - 14, 24, 24, 0, 360);

    // Lower-left diagonal
    setColour(orange);
    fillArc(x3 - 14, y3 + 20, 24, 24, 0, 360);

    // Lower-right diagonal
    setColour(green);
    fillArc(x3 + 20, y3 + 20, 24, 24, 0, 360);

    // Centre
    setColour(yellow);
    fillArc(x3, y3, 30, 30, 0, 360);

    return 0;
}