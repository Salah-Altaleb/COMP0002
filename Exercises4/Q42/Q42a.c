#include "graphics.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int CANVAS_WIDTH = 500;
    int CANVAS_HEIGHT = 500;
    setWindowSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    int squareSize = 50;
    int cols = 10;       
    int rows = 10;       

    background();
    
    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            if ((row + col) % 2 == 0)
                setColour(white);
            else
                setColour(black);

            fillRect(col * squareSize, row * squareSize, squareSize, squareSize);
        }
    }

    foreground();
    srand(time(NULL));

    int ballX = 250;
    int ballY = 250;
    int ballRadius = 15;

    double vx = 3;
    double vy = 2;

    int loops = 10000;
    int i = 0;
    while (i <= loops)
    {
        clear();

        ballX += (int)vx;
        ballY += (int)vy;

        if (ballX - ballRadius <= 0 || ballX + ballRadius >= 500)
        {
            vx = -vx;
            vy += (rand() % 5 - 2); // change vy by -2 to +2
        }

        if (ballY - ballRadius <= 0 || ballY + ballRadius >= 500)
        {
            vy = -vy;
            vx += (rand() % 5 - 2);
        }

        if (vx > 5) vx = 5;
        if (vx < -5) vx = -5;
        if (vy > 5) vy = 5;
        if (vy < -5) vy = -5;

        // Draw the ball
        setColour(red);
        fillArc(ballX - ballRadius, ballY - ballRadius, 2 * ballRadius, 2 * ballRadius, 0, 360);

        sleep(20);
        i++;
    }

    return 0;
}
