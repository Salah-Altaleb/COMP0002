#include "maze.h"
#include "graphics.h"
#include <stdio.h>
#include <time.h>

static int **alloc_int_grid(int cols, int rows) {
    int **grid = malloc(cols * sizeof(int*));
    if (!grid) return NULL;
    for (int c = 0; c < cols; ++c) {
        grid[c] = calloc(rows, sizeof(int));
        if (!grid[c]) {
            // free partial
            for (int i = 0; i < c; ++i) free(grid[i]);
            free(grid);
            return NULL;
        }
    }
    return grid;
}

int maze_init(Maze *m, int canvasW, int canvasH, int tileSize, int padding) {
    if (!m) return 0;
    m->tileSize = tileSize;
    m->padding = padding;
    // compute usable area and the number of tiles vertically and horizontally
    int usableW = canvasW - 2 * padding;
    int usableH = canvasH - 2 * padding;
    if (usableW <= 0 || usableH <= 0) return 0;
    m->cols = usableW / tileSize;
    m->rows = usableH / tileSize;
    if (m->cols <= 0 || m->rows <= 0) return 0;

    m->wall = alloc_int_grid(m->cols, m->rows);
    m->marker = alloc_int_grid(m->cols, m->rows);
    if (!m->wall || !m->marker) return 0;

    // place surrounding walls (edge tiles flagged as walls)
    for (int c = 0; c < m->cols; ++c) {
        m->wall[c][0] = 1;
        m->wall[c][m->rows - 1] = 1;
    }
    for (int r = 0; r < m->rows; ++r) {
        m->wall[0][r] = 1;
        m->wall[m->cols - 1][r] = 1;
    }

    // empty markers initially
    return 1;
}

void maze_free(Maze *m) {
    if (!m) return;
    if (m->wall) {
        for (int c = 0; c < m->cols; ++c) free(m->wall[c]);
        free(m->wall);
        m->wall = NULL;
    }
    if (m->marker) {
        for (int c = 0; c < m->cols; ++c) free(m->marker[c]);
        free(m->marker);
        m->marker = NULL;
    }
}

void maze_tile_to_pixel(Maze *m, int col, int row, int *outX, int *outY) {
    if (!m || !outX || !outY) return;
    *outX = m->padding + col * m->tileSize;
    *outY = m->padding + row * m->tileSize;
}

void maze_draw(Maze *m) {
    if (!m) return;
    // draw tiles
    for (int r = 0; r < m->rows; ++r) {
        for (int c = 0; c < m->cols; ++c) {
            int px, py;
            maze_tile_to_pixel(m, c, r, &px, &py);
            setColour(white);
            fillRect(px, py, m->tileSize - 1, m->tileSize - 1);
            setColour(black);
            drawRect(px, py, m->tileSize - 1, m->tileSize - 1);
        }
    }
    // draw border
    setColour(red);
    drawRect(m->padding - 1, m->padding - 1, m->cols * m->tileSize + 1, m->rows * m->tileSize + 1);

    // draw walls (fill cell with dark grey)
    for (int r = 0; r < m->rows; ++r) {
        for (int c = 0; c < m->cols; ++c) {
            if (m->wall[c][r]) {
                int px, py;
                maze_tile_to_pixel(m, c, r, &px, &py);
                setColour(darkgray);
                fillRect(px+1, py+1, m->tileSize-2, m->tileSize-2);
            }
        }
    }
}

// draw markers
void maze_draw_markers(Maze *m) {
    for (int r = 0; r < m->rows; ++r) {
        for (int c = 0; c < m->cols; ++c) {
            if (m->marker[c][r]) {
                int px, py;
                maze_tile_to_pixel(m, c, r, &px, &py);
                int cx = px + m->tileSize / 2;
                int cy = py + m->tileSize / 2;
                int rad = m->tileSize / 2; // was 5
                setColour(green);
                fillOval(cx - rad, cy - rad, 2 * rad, 2 * rad);
            }
        }
    }
}

int maze_is_wall_tile(Maze *m, int col, int row) {
    if (!m) return 1;
    if (col < 0 || col >= m->cols || row < 0 || row >= m->rows) return 1;
    return m->wall[col][row];
}
int maze_has_marker_tile(Maze *m, int col, int row) {
    if (!m) return 0;
    if (col < 0 || col >= m->cols || row < 0 || row >= m->rows) return 0;
    return m->marker[col][row];
}
void maze_remove_marker(Maze *m, int col, int row) {
    if (!m) return;
    if (col < 0 || col >= m->cols || row < 0 || row >= m->rows) return;
    m->marker[col][row] = 0;
}

int maze_place_random_marker_next_to_wall(Maze *m) {
    if (!m) return 0;
    // collect candidate tiles that are NOT wall and have at least one orthogonal neighbor that IS wall
    int capacity = m->cols * m->rows;
    int *candidates = malloc(capacity * sizeof(int)); // store index = col + row*cols
    int count = 0;
    for (int r = 1; r < m->rows - 1; ++r) {
        for (int c = 1; c < m->cols - 1; ++c) {
            if (m->wall[c][r]) continue;
            // check neighbors
            if (m->wall[c-1][r] || m->wall[c+1][r] || m->wall[c][r-1] || m->wall[c][r+1]) {
                candidates[count++] = c + r * m->cols;
            }
        }
    }
    if (count == 0) {
        free(candidates);
        return 0;
    }
    int idx = rand() % count;
    int val = candidates[idx];
    int col = val % m->cols;
    int row = val / m->cols;
    m->marker[col][row] = 1;
    free(candidates);
    return 1;
}
