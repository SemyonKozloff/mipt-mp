#include <stdlib.h>
#include <assert.h>

#include "omp-gol.h"

#define ALIVE 1
#define DEAD 0

bool calc_new_generation(size_t x_grid_size, size_t y_grid_size,
                         char **curr_generation, char **new_generation)
{
    bool is_changed = false;
#pragma omp parallel shared(curr_generation, new_generation)
    {
        // TODO try auto mb
#pragma omp for reduction(||, is_changed) schedule (dynamic) nowait
        for (size_t i = 1; i < x_grid_size + 1; ++i) {
            // TODO try inner parallel for mb
            for (size_t j = 1; j < y_grid_size + 1; ++j) {
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
    }

    return is_changed;
}

void start_gol(size_t x_grid_size, size_t y_grid_size,
               size_t num_threads)
{
    char **curr_generation = alloc_grid(x_grid_size, y_grid_size);
    char **new_generation = alloc_grid(x_grid_size, y_grid_size)
    set_init_generation(x_grid_size, y_grid_size, curr_generation);
    bool is_changed = true;

    while (is_changed)
    {
        is_changed = calc_new_generation(x_grid_size, y_grid_size,
                                         curr_generation, new_generation);

    }
}

char **alloc_grid(size_t x_grid_size, size_t y_grid_size)
{
    return NULL;
}



