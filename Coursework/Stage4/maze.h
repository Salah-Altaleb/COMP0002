#ifndef MAZE_H
#define MAZE_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct Maze {
    int cols;       // number of tiles horizontally
    int rows;       // number of tiles vertically
    int tileSize;   // pixel size of a tile
    int padding;    // pixel padding from edges
    int **wall;     // wall[col][row] -> 1 if wall
    int **marker;   // marker[col][row] -> 1 if marker exists
} Maze;

// Initialize maze structure (allocates internal arrays). Returns 0 on success.
int maze_init(Maze *m, int canvasW, int canvasH, int tileSize, int padding);

// Free allocated arrays
void maze_free(Maze *m);

// Draw the arena (tiles, walls border, markers) using graphics.h calls.
void maze_draw(Maze *m);

// Draw the Markers
void maze_draw_markers(Maze *m);

// Place a marker in a random tile that is adjacent to a wall (not on the wall itself).
// Returns 1 on success, 0 if it couldn't place (shouldn't happen in normal arena).
int maze_place_random_marker(Maze *m);

// Check tile bounds and wall/marker queries:
int maze_is_wall_tile(Maze *m, int col, int row);
int maze_has_marker_tile(Maze *m, int col, int row);
void maze_remove_marker(Maze *m, int col, int row);

void add_random_obstacle(Maze *maze);

// Convert tile -> pixel coordinates for drawing (top-left of tile)
void maze_tile_to_pixel(Maze *m, int col, int row, int *outX, int *outY);

bool is_fully_connected(Maze *maze);

void dfs_fill(Maze *maze, int **visited, int r, int c);

#endif // MAZE_H
