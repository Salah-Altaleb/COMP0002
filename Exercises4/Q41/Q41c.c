#include "graphics.h"
#include <math.h>
#include <stdio.h>

int main(void)
{
    // Opening coordinates file, retrieving and storing values
    int x[100], y[100];
    int n = 0;

    FILE *file = fopen("coordinates.txt", "r");
    if (file == NULL) {
        message("Error: cannot open coordinates file.");
        return 1;
    }

    while (fscanf(file, "%d %d", &x[n], &y[n]) == 2) {
        n++;
    }
    fclose(file);

    int cx = 250; 
    int cy = 150;
    int r = 50;       
    int size = 25;  

    // Draw the circle (background)
    background();
    setColour(green);
    fillArc(cx - r, cy - r, 2 * r, 2 * r, 0, 360);
    setColour(white);
    fillArc(cx - r + 15, cy - r + 15, 2 * (r - 15), 2 * (r - 15), 0, 360);

    foreground();
    for (int i = 0; i < n; i++) {
        clear();
        setColour(blue);
        fillRect(x[i] - size / 2, y[i] - size / 2, size, size);
        sleep(200);
    }

    return 0;
}
