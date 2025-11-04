#include "graphics.h"

int main(void)
{
    // Rectangle 1
    drawLine(30, 30, 110, 30); // Top
    drawLine(110, 30, 110, 80); // Right
    drawLine(30, 80, 110, 80); // Bottom
    drawLine(30, 30, 30, 80); // Left

    // Rectangle 2
    drawRect(150, 50, 60, 140);
    return 0;
}
