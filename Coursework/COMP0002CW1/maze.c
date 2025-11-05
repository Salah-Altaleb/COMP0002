#include "maze.h"
#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static int **alloc_int_grid(int cols, int rows) {
    int **grid = malloc(cols * sizeof(int*));
    if (!grid) return NULL;

    for (int c = 0; c < cols; ++c) {
        grid[c] = calloc(rows, sizeof(int));
        if (!grid[c]) {
            for (int i = 0; i < c; ++i) free(grid[i]);
            free(grid);
            return NULL;
        }
    }

    return grid;
}

int maze_init(Maze *m, int canvas_width, int canvas_height, int tile_size, int padding) {
    if (!m) return 0;

    m->tile_size = tile_size;
    m->padding = padding;

    int usable_width = canvas_width - 2 * padding;
    int usable_height = canvas_height - 2 * padding;

    if (usable_width <= 0 || usable_height <= 0) return 0;

    m->cols = usable_width / tile_size;
    m->rows = usable_height / tile_size;

    if (m->cols <= 0 || m->rows <= 0) return 0;

    m->wall = alloc_int_grid(m->cols, m->rows);
    m->marker = alloc_int_grid(m->cols, m->rows);
    if (!m->wall || !m->marker) return 0;

    // Surrounding walls
    for (int c = 0; c < m->cols; ++c) {
        m->wall[c][0] = 1;
        m->wall[c][m->rows - 1] = 1;
    }
    for (int r = 0; r < m->rows; ++r) {
        m->wall[0][r] = 1;
        m->wall[m->cols - 1][r] = 1;
    }

    if (!maze_generate_special_arena(m, canvas_width, canvas_height, tile_size, padding)) {
        fprintf(stderr, "Failed to generate special arena.\n");
        maze_free(m);
        return 0;
    }

    return 1;
}

int maze_generate_special_arena(Maze *m, int canvas_width, int canvas_height, int tile_size, int padding) {
    int top_row = 1;
    int base_row = m->rows - 2;
    int center_col = m->cols / 2;
    int max_half_width = m->cols / 2;

    // Step 1: Fill triangular region
    for (int row = top_row; row <= base_row; ++row) {
        double frac = (double)(row - top_row) / (double)(base_row - top_row);
        int half_width = (int)(frac * max_half_width);
        int left_col = center_col - half_width;
        int right_col = center_col + half_width;

        for (int col = left_col; col <= right_col; ++col) {
            if (col <= 0 || col >= m->cols - 1 || row <= 0 || row >= m->rows - 1)
                continue;
            if (m->wall[col][row]) continue;

            m->wall[col][row] = 1;
            if (!is_fully_connected(m))
                m->wall[col][row] = 0;
        }
    }

    // Step 2: Invert interior
    for (int r = 1; r < m->rows - 1; r++) {
        for (int c = 1; c < m->cols - 1; c++) {
            m->wall[c][r] = !m->wall[c][r];
        }
    }

    // Step 3: Retry if disconnected
    int retries = 0;
    while (retries < 5 && !is_fully_connected(m)) {
        printf("Maze disconnected after inversion. Retrying (%d)...\n", retries + 1);
        retries++;

        maze_free(m);
        if (!maze_init(m, canvas_width, canvas_height, tile_size, padding))
            fprintf(stderr, "Failed to regenerate maze after disconnection.\n");
        return 0;
    }

    if (retries == 5) {
        fprintf(stderr, "Maze generation failed after 5 attempts.\n");
        return 0;
    }

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

void maze_tile_to_pixel(Maze *m, int col, int row, int *out_x, int *out_y) {
    if (!m || !out_x || !out_y) return;
    *out_x = m->padding + col * m->tile_size;
    *out_y = m->padding + row * m->tile_size;
}

void maze_draw(Maze *m) {
    if (!m) return;

    for (int r = 0; r < m->rows; ++r) {
        for (int c = 0; c < m->cols; ++c) {
            int px, py;
            maze_tile_to_pixel(m, c, r, &px, &py);

            setColour(white);
            fillRect(px, py, m->tile_size - 1, m->tile_size - 1);

            setColour(black);
            drawRect(px, py, m->tile_size - 1, m->tile_size - 1);
        }
    }

    setColour(red);
    drawRect(m->padding - 1, m->padding - 1, m->cols * m->tile_size + 1, m->rows * m->tile_size + 1);

    for (int r = 0; r < m->rows; ++r) {
        for (int c = 0; c < m->cols; ++c) {
            if (m->wall[c][r]) {
                int px, py;
                maze_tile_to_pixel(m, c, r, &px, &py);
                setColour(darkgray);
                fillRect(px + 1, py + 1, m->tile_size - 2, m->tile_size - 2);
            }
        }
    }
}

void maze_draw_markers(Maze *m) {
    for (int r = 0; r < m->rows; ++r) {
        for (int c = 0; c < m->cols; ++c) {
            if (m->marker[c][r]) {
                int px, py;
                maze_tile_to_pixel(m, c, r, &px, &py);
                int cx = px + m->tile_size / 2;
                int cy = py + m->tile_size / 2;
                int rad = m->tile_size / 2;
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

int maze_place_random_marker(Maze *m) {
    if (!m) return 0;

    int capacity = m->cols * m->rows;
    int *candidates = malloc(capacity * sizeof(int));
    int count = 0;

    for (int r = 1; r < m->rows - 1; ++r) {
        for (int c = 1; c < m->cols - 1; ++c) {
            if (m->wall[c][r] || m->marker[c][r]) continue;
            candidates[count++] = c + r * m->cols;
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

void add_random_obstacle(Maze *m) {
    int row, col;
    int tries = 0;

    while (tries < 1000) {
        row = rand() % m->rows;
        col = rand() % m->cols;
        tries++;

        if (m->wall[col][row] == 1 || row == 0 || col == 0 || row == m->rows - 1 || col == m->cols - 1)
            continue;

        m->wall[col][row] = 1;

        if (is_fully_connected(m)) return;

        m->wall[col][row] = 0;
    }

    printf("Warning: Could not place more obstacles without disconnecting maze.\n");
}

bool is_fully_connected(Maze *m) {
    int rows = m->rows;
    int cols = m->cols;

    int **visited = malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; ++i) visited[i] = calloc(cols, sizeof(int));

    int start_row = -1, start_col = -1;
    for (int r = 0; r < rows && start_row == -1; ++r) {
        for (int c = 0; c < cols && start_col == -1; ++c) {
            if (m->wall[c][r] == 0) {
                start_row = r;
                start_col = c;
            }
        }
    }

    if (start_row == -1) {
        for (int i = 0; i < rows; ++i) free(visited[i]);
        free(visited);
        return true;
    }

    dfs_fill(m, visited, start_row, start_col);

    int total_free = 0, total_visited = 0;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (m->wall[c][r] == 0) total_free++;
            if (visited[r][c]) total_visited++;
        }
    }

    for (int i = 0; i < rows; ++i) free(visited[i]);
    free(visited);

    return total_free == total_visited;
}

void dfs_fill(Maze *m, int **visited, int row, int col) {
    if (row < 0 || col < 0 || row >= m->rows || col >= m->cols) return;
    if (m->wall[col][row] == 1 || visited[row][col]) return;

    visited[row][col] = 1;

    dfs_fill(m, visited, row + 1, col);
    dfs_fill(m, visited, row - 1, col);
    dfs_fill(m, visited, row, col + 1);
    dfs_fill(m, visited, row, col - 1);
}