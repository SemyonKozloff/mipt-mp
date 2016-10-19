#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <memory.h>

#include "omp-gol.h"

void launch_game(size_t x_grid_size, size_t y_grid_size,
                 size_t num_generations)
{
    char **curr_generation = alloc_grid(x_grid_size, y_grid_size);
    char **new_generation = alloc_grid(x_grid_size, y_grid_size);
    set_init_generation(x_grid_size, y_grid_size, curr_generation);
    bool is_changed = true;

    //#pragma omp parallel shared(curr_generation, new_generation, is_changed)
    {
        for (size_t generation_counter = 0;
             generation_counter < num_generations && is_changed;
             ++generation_counter)
        {
            //#pragma omp master
            {
                display_grid(x_grid_size, y_grid_size, curr_generation);
            }

            is_changed = false;
            // calculate new generation based on the previous one
            #pragma omp parallel for reduction(||: is_changed) schedule (dynamic, 2) shared(curr_generation, new_generation)
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

                    if (num_alive == 2)
                    {
                        new_generation[i][j] = curr_generation[i][j];
                    }
                    else if (num_alive == 3)
                    {
                        new_generation[i][j] = ALIVE;
                    }
                    else if (num_alive < 2 || num_alive > 3)
                    {
                        new_generation[i][j] = DEAD;
                    }

                    if (new_generation[i][j] != curr_generation[i][j])
                    {
                        is_changed = true;
                    }
                }
            }

            SWAP(curr_generation, new_generation);

            // implicitly flush
            //#pragma omp barrier
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

void copy_grid(size_t x_grid_size, size_t y_grid_size,
               char **to, char **from)
{
    for (size_t i = 0; i < x_grid_size + 2; ++i)
    {
        memcpy(to[i], from[i], (y_grid_size + 2) * sizeof(char));
    }
}

// далее идет дикий говнокод

void set_init_generation(size_t x_grid_size, size_t y_grid_size,
                         char **init_generation)
{
    // just for test
    FILE* input_file = fopen("/home/semyon/Projects/mipt-multiprocessing/omp-gol/test/input.txt", "r");
    assert(input_file != NULL);
    char n = '\0';

    for (size_t i = 1; i < x_grid_size + 1; ++i)
    {
        fread(init_generation[i] + 1, sizeof(char),
              y_grid_size, input_file);
        fread(&n, sizeof(char), 1, input_file);
    }

    for (size_t i = 1; i < x_grid_size + 1; ++i)
    {
        for (size_t j = 1; j < y_grid_size + 1; ++j)
        {
            init_generation[i][j] -= '0';
        }
    }

    fclose(input_file);
}

void display_grid(size_t x_grid_size, size_t y_grid_size, char **generation)
{
    for (size_t i = 1; i < x_grid_size + 1; ++i)
    {
        for (size_t j = 1; j < y_grid_size + 1; ++j)
        {
            generation[i][j] == 1 ? printf("#") : printf("0");
        }
        printf("\n");
    }

    printf("\n\n");
}



