#include "graphics.h"

int main(void)
{
    int centreX = 300;

    drawRect(centreX - 20, 100, 40, 120);
    drawOval(centreX - 40, 80, 80, 20);
    drawRect(centreX - 10, 40, 20, 40);
    drawLine(centreX, 40, centreX, 0);

    return 0;
}
