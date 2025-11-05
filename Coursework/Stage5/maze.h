#ifndef MAZE_H
#define MAZE_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct Maze {
    int cols;
    int rows;
    int tileSize;
    int padding;
    int **wall;
    int **marker;
} Maze;

int maze_init(Maze *m, int canvasW, int canvasH, int tileSize, int padding);

int maze_generate_special_arena(Maze *m, int canvasW, int canvasH, int tileSize, int padding);

void maze_free(Maze *m);

void maze_draw(Maze *m);

void maze_draw_markers(Maze *m);

int maze_place_random_marker(Maze *m);

int maze_is_wall_tile(Maze *m, int col, int row);
int maze_has_marker_tile(Maze *m, int col, int row);
void maze_remove_marker(Maze *m, int col, int row);

void add_random_obstacle(Maze *maze);

void maze_tile_to_pixel(Maze *m, int col, int row, int *outX, int *outY);

bool is_fully_connected(Maze *maze);

void dfs_fill(Maze *maze, int **visited, int r, int c);

#endif // MAZE_H
