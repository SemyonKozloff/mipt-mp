#include <cstdlib>
#include <random>
#include <stdexcept>
#include <iostream>

#include "omp_gameoflife.h"

omp_gameoflife::omp_gameoflife(const omp_gameoflife::grid_t& init_generation)
        : gameoflife(init_generation)
{ }

void omp_gameoflife::launch(std::size_t num_generations)
{
    bool is_changed = true;

    for (std::size_t step_counter = 0;
         step_counter < num_generations && is_changed;
         ++step_counter, ++generation_counter_)
    {
        is_changed = false;

        #pragma omp parallel for schedule (dynamic) reduction(||: is_changed)
        for (std::size_t x = 1; x < x_grid_size_ - 1; ++x) {
            for (std::size_t y = 1; y < y_grid_size_ - 1; ++y) {
                std::size_t num_live = get_num_live_(x, y);

                if (num_live == 2) {
                    next_generation_[x][y] = current_generation_[x][y];
                }
                else if (num_live == 3) {
                    next_generation_[x][y] = LIVE_;
                }
                else if (num_live < 2 || num_live > 3) {
                    next_generation_[x][y] = DEAD_;
                }

                if (current_generation_[x][y] != next_generation_[x][y]) {
                    is_changed = true;
                }
            }
        }

        std::swap(current_generation_, next_generation_);
    }
}