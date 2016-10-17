#ifndef MIPT_MP_OMP_GOL_H
#define MIPT_MP_OMP_GOL_H

#include <stdbool.h>
#include <stddef.h>

/*
 * Calculate new generation based on previous one.
 * Return TRUE if at least one cell was changed in new generation.
 */
bool calc_new_generation(size_t x_grid_size, size_t y_grid_size,
                         char **curr_generation,
                         char **new_generation);

void start_gol(size_t x_grid_size, size_t y_grid_size,
               size_t num_threads);

void stop_gol(char **prev_generation,
              char **curr_generation);

void set_init_generation(size_t x_grid_size, size_t y_grid_size,
                         char **init_generation);

char **alloc_grid(size_t x_grid_size, size_t y_grid_size);
void free_grid(char **grid);

#endif //MIPT_MP_OMP_GOL_H
