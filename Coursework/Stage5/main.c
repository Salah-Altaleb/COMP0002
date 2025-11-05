#include "maze.h"
#include "robot.h"
#include "graphics.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    srand((unsigned)time(NULL));

    int TILE_SIZE = 20;
    int PADDING = 1 * TILE_SIZE;
    int numObstacles = 0;
    int numMarkers = 10;

    int cols = 29;
    int rows = 29;

    int CANVAS_WIDTH = cols * TILE_SIZE;
    int CANVAS_HEIGHT = rows * TILE_SIZE;

    int delay_ms = 100;

    Maze maze;
    Robot robot;

    background();
    setWindowSize(CANVAS_WIDTH, CANVAS_HEIGHT);

    if (!maze_init(&maze, CANVAS_WIDTH, CANVAS_HEIGHT, TILE_SIZE, PADDING)) {
        fprintf(stderr, "Failed to init maze\n");
        maze_free(&maze);
        return 1;
    }

    // Draw the static maze once on the background
    background();
    for (int i = 0; i < numObstacles; ++i) {
        add_random_obstacle(&maze);
    }
    maze_draw(&maze);

    for (int i = 0; i < numMarkers; ++i) {
        if (!maze_place_random_marker(&maze)) {
            fprintf(stderr, "Failed to place marker\n");
            maze_free(&maze);
            return 1;
        }
    }

    if (!robot_init_random(&robot, &maze)) {
        fprintf(stderr, "Failed to place robot\n");
        maze_free(&maze);
        return 1;
    }

    // Main loop: update foreground only
    dfs_find_marker(&robot, delay_ms);

    render_state(&robot, delay_ms);

    sleep(delay_ms * 5);
    maze_free(&maze);
    robot_free(&robot);
    return 0;
}



/* 
Valgrind output for main.c:
    HEAP SUMMARY:
==576==     in use at exit: 0 bytes in 0 blocks
==576==   total heap usage: 9,504 allocs, 9,504 frees, 1,094,848 bytes allocated
==576==
==576== All heap blocks were freed -- no leaks are possible
==576==
==576== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
*/