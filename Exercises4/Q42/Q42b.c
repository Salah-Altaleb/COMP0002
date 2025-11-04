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
    // Draw checkered pattern
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

    // === Multiple Balls ===
    int numBalls = 5;
    int ballRadius[5] = {10, 12, 15, 8, 20};
    int ballX[5];
    int ballY[5];
    double vx[5];
    double vy[5];
    int colours[5] = {red, blue, green, yellow, magenta};

    // Initialize random positions and velocities
    for (int i = 0; i < numBalls; i++)
    {
        ballX[i] = rand() % (CANVAS_WIDTH - 2 * ballRadius[i]) + ballRadius[i];
        ballY[i] = rand() % (CANVAS_HEIGHT - 2 * ballRadius[i]) + ballRadius[i];
        vx[i] = (rand() % 5 + 2) * (rand() % 2 == 0 ? 1 : -1);  // random direction
        vy[i] = (rand() % 5 + 2) * (rand() % 2 == 0 ? 1 : -1);
    }

    // === Animation loop ===
    int loops = 10000;
    for (int frame = 0; frame < loops; frame++)
    {
        clear();

        // Move and draw all balls
        for (int i = 0; i < numBalls; i++)
        {
            ballX[i] += (int)vx[i];
            ballY[i] += (int)vy[i];

            // Bounce on walls
            if (ballX[i] - ballRadius[i] <= 0 || ballX[i] + ballRadius[i] >= CANVAS_WIDTH)
            {
                vx[i] = -vx[i];
                vy[i] += (rand() % 5 - 2);
            }
            if (ballY[i] - ballRadius[i] <= 0 || ballY[i] + ballRadius[i] >= CANVAS_HEIGHT)
            {
                vy[i] = -vy[i];
                vx[i] += (rand() % 5 - 2);
            }

            // Clamp speeds
            if (vx[i] > 6) vx[i] = 6;
            if (vx[i] < -6) vx[i] = -6;
            if (vy[i] > 6) vy[i] = 6;
            if (vy[i] < -6) vy[i] = -6;

            // Draw ball
            setColour(colours[i]);
            fillArc(ballX[i] - ballRadius[i], ballY[i] - ballRadius[i],
                    2 * ballRadius[i], 2 * ballRadius[i], 0, 360);
        }

        sleep(20);
    }

    return 0;
}
