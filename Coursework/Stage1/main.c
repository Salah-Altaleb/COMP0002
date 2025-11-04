#include "maze.h"
#include "robot.h"
#include "graphics.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    srand((unsigned)time(NULL));

    int CANVAS_WIDTH = 600;
    int CANVAS_HEIGHT = 600;
    int TILE_SIZE = 40;
    int PADDING = 1 * TILE_SIZE;

    Maze maze;
    Robot robot;

    background();
    setWindowSize(CANVAS_WIDTH, CANVAS_HEIGHT);

    if (!maze_init(&maze, CANVAS_WIDTH, CANVAS_HEIGHT, TILE_SIZE, PADDING)) {
        fprintf(stderr, "Failed to init maze\n");
        maze_free(&maze);
        return 1;
    }

    if (!maze_place_random_marker_next_to_wall(&maze)) {
        fprintf(stderr, "Failed to place marker\n");
        maze_free(&maze);
        return 1;
    }

    if (!robot_init_random(&robot, &maze)) {
        fprintf(stderr, "Failed to place robot\n");
        maze_free(&maze);
        return 1;
    }

    // Draw the static maze once on the background
    background();
    maze_draw(&maze);

    // Main loop: update foreground only
    int steps = 0;
    while (1) {
        foreground();
        clear();

        // Draw markers + robot
        maze_draw_markers(&maze);
        robot_draw(&robot);

        if (atMarker(&robot)) {
            pickUpMarker(&robot);
            // Redraw to show robot on now-empty tile
            foreground();
            clear();
            maze_draw_markers(&maze);
            robot_draw(&robot);
            break;
        }

        if (canMoveForward(&robot)) {
            forward(&robot);
        } else {
            right(&robot);
        }

        sleep(200);
        steps++;
        if (steps > 2000) break;
    }

    sleep(1000);
    maze_free(&maze);
    return 0;
}