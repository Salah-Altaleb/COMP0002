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
    int num_obstacles = 0;
    int num_markers = 10;

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

    background();
    for (int i = 0; i < num_obstacles; ++i) {
        add_random_obstacle(&maze);
    }
    maze_draw(&maze);

    for (int i = 0; i < num_markers; ++i) {
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