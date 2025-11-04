#include "graphics.h"
#include <stdio.h>

int main(void) 
{ 
    // Draw axes
    drawLine(50, 250, 50, 40); // y-axis
    drawLine(50, 250, 450, 250); // x-axis

    // Y-axis labels
    for (int i = 0; i < 5; i++) {
        int y = 250 - i * 50;
        drawLine(45, y, 50, y);
    }
    drawString("0", 20, 255);
    drawString("50", 20, 205);
    drawString("100", 20, 155);
    drawString("150", 20, 105);
    drawString("200", 20, 55);

    // X-axis labels
    drawString("A", 100, 265);
    drawString("B", 200, 265);
    drawString("C", 300, 265);
    drawString("D", 400, 265);

    // Draw bars
    setColour(red);
    fillRect(50, 250 - 120, 100, 120); // Bar A
    setColour(blue);
    fillRect(150, 250 - 80, 100, 80); // Bar B
    setColour(green);
    fillRect(250, 250 - 200, 100, 200); // Bar C
    setColour(yellow);
    fillRect(350, 250 - 160, 100, 160); // Bar D

    return 0;
}