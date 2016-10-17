#include <stdlib.h>
#include <assert.h>
#include <memory.h>

#include "omp-gol.h"

/*
bool calc_new_generation(size_t x_grid_size, size_t y_grid_size,
                         char **curr_generation, char **new_generation)
{
    bool is_changed = false;
#pragma omp parallel shared(curr_generation, new_generation)
    {
        // TODO mb try auto
#pragma omp for reduction(||: is_changed) schedule (dynamic) nowait
        for (size_t i = 1; i < x_grid_size + 1; ++i)
        {
            // TODO mb try inner parallel for
            for (size_t j = 1; j < y_grid_size + 1; ++j)
            {
                char num_alive = curr_generation[i][j + 1]
                                 + curr_generation[i][j - 1]
                                 + curr_generation[i + 1][j]
                                 + curr_generation[i - 1][j]
                                 + curr_generation[i - 1][j - 1]
                                 + curr_generation[i - 1][j + 1]
                                 + curr_generation[i + 1][j - 1]
                                 + curr_generation[i + 1][j + 1];
                assert(0 <= num_alive && num_alive <= 8);

                char prev_state = new_generation[i][j];
                if (num_alive == 3)
                {
                    new_generation[i][j] = ALIVE;
                }
                else if (num_alive < 2 || num_alive > 3)
                {
                    new_generation[i][j] = DEAD;
                }
                if (prev_state != new_generation[i][j])
                {
                    is_changed = true;
                }
            }
        }
    }

    return is_changed;
}
*/

void start_gol(size_t x_grid_size, size_t y_grid_size)
{
    char **curr_generation = alloc_grid(x_grid_size, y_grid_size);
    char **new_generation = alloc_grid(x_grid_size, y_grid_size);
    set_init_generation(x_grid_size, y_grid_size, curr_generation);
    bool is_changed = true;

#pragma omp parallel shared(curr_generation, new_generation, is_changed)
    {
        while (is_changed)
        {
#pragma omp master
            {
                draw_grid(x_grid_size, y_grid_size, curr_generation);
            }

            is_changed = false;
            // calculate new generation based on the previous one
#pragma omp for reduction(||: is_changed) schedule (dynamic) nowait
            for (size_t i = 1; i < x_grid_size + 1; ++i)
            {
                // TODO mb try inner parallel for
                for (size_t j = 1; j < y_grid_size + 1; ++j)
                {
                    char num_alive = curr_generation[i][j + 1]
                                     + curr_generation[i][j - 1]
                                     + curr_generation[i + 1][j]
                                     + curr_generation[i - 1][j]
                                     + curr_generation[i - 1][j - 1]
                                     + curr_generation[i - 1][j + 1]
                                     + curr_generation[i + 1][j - 1]
                                     + curr_generation[i + 1][j + 1];
                    assert(0 <= num_alive && num_alive <= 8);

                    char prev_state = new_generation[i][j];
                    if (num_alive == 3) {
                        new_generation[i][j] = ALIVE;
                    }
                    else if (num_alive < 2 || num_alive > 3) {
                        new_generation[i][j] = DEAD;
                    }
                    if (prev_state != new_generation[i][j]) {
                        is_changed = true;
                    }
                }
            }

#pragma omp barrier
            SWAP(curr_generation, new_generation);
        }
    }

    free_grid(x_grid_size, curr_generation);
    free_grid(x_grid_size, new_generation);
}

char **alloc_grid(size_t x_grid_size, size_t y_grid_size)
{
    char **new_grid = (char**)malloc((x_grid_size + 2) * sizeof(char*));
    assert(new_grid != NULL);

    for (size_t i = 0; i < y_grid_size + 2; ++i)
    {
        new_grid[i] = (char*)calloc(y_grid_size + 2, sizeof(char));
        assert(new_grid[i] != NULL);
    }
    return new_grid;
}

void free_grid(size_t x_grid_size, char **grid)
{
    for (size_t i = 0; i < x_grid_size + 2; ++i)
    {
        free(grid[i]);
    }
    free(grid);
}

void set_init_generation(size_t x_grid_size, size_t y_grid_size,
                         char **init_generation)
{

}

void copy_grid(size_t x_grid_size, size_t y_grid_size,
               char **to, char **from)
{
    for (size_t i = 0; i < x_grid_size + 2; ++i)
    {
        memcpy(to[i], from[i], (y_grid_size + 2) * sizeof(char));
    }
}

void draw_grid(size_t x_grid_size, size_t y_grid_size,
               char **generation)
{

}



