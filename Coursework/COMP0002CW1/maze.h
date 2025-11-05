#ifndef MAZE_H
#define MAZE_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct Maze {
    int cols;
    int rows;
    int tile_size;
    int padding;
    int **wall;
    int **marker;
} Maze;

int maze_init(Maze *m, int canvas_width, int canvas_height, int tile_size, int padding);
int maze_generate_special_arena(Maze *m, int canvas_width, int canvas_height, int tile_size, int padding);
void maze_free(Maze *m);

void maze_tile_to_pixel(Maze *m, int col, int row, int *out_x, int *out_y);

void maze_draw(Maze *m);
void maze_draw_markers(Maze *m);

int maze_is_wall_tile(Maze *m, int col, int row);
int maze_has_marker_tile(Maze *m, int col, int row);
void maze_remove_marker(Maze *m, int col, int row);

int maze_place_random_marker(Maze *m);

void add_random_obstacle(Maze *m);

bool is_fully_connected(Maze *m);
void dfs_fill(Maze *m, int **visited, int row, int col);

#endif // MAZE_H