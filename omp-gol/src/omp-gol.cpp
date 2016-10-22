#include <cstdlib>
#include <random>
#include <stdexcept>
#include <iostream>

#include <omp.h>

#include "omp-gol.h"

const game_of_life::state_t game_of_life::DEAD;
const game_of_life::state_t game_of_life::LIVE;

game_of_life::game_of_life(const game_of_life::grid_t& init_generation)
        : generation_counter_(0),
          x_grid_size_(init_generation.size() + 2),
          y_grid_size_(init_generation[0].size() + 2),
          current_generation_(init_generation),
          next_generation_(grid_t(x_grid_size_, row_t(y_grid_size_)))
{
    // adding borders
    for (auto&& row : current_generation_)
    {
        row.insert(std::begin(row), DEAD);
        row.push_back(DEAD);
    }

    // side borders
    current_generation_.insert(std::begin(current_generation_),
                               row_t(y_grid_size_, DEAD));
    current_generation_.push_back(row_t(y_grid_size_, DEAD));
}

void game_of_life::launch(std::size_t num_generations)
{
    bool is_changed = true;

    for (std::size_t step_counter = 0;
         step_counter < num_generations && is_changed;
         ++step_counter, ++generation_counter_)
    {
        display_grid(current_generation_);

        is_changed = false;
        // avoiding borders
        for (std::size_t i = 1; i < x_grid_size_ - 1; ++i)
        {
            for (std::size_t j = 1; i < y_grid_size_ - 1; ++j)
            {
                std::size_t num_live = get_num_live_(i, j);
                if (num_live == 2)
                {
                    next_generation_[i][j] = current_generation_[i][j];
                }
                else if (num_live == 3)
                {
                    next_generation_[i][j] = LIVE;
                }
                else if (num_live < 2 || num_live > 3)
                {
                    next_generation_[i][j] = DEAD;
                }

                if (current_generation_[i][j] != next_generation_[i][j])
                {
                    is_changed = true;
                }
            }
        }

        std::swap(current_generation_, next_generation_);
    }
}

game_of_life::grid_t game_of_life::get_random_generation(std::size_t x_grid_size,
                                                         std::size_t y_grid_size)
{
    grid_t random_generation(x_grid_size, row_t(y_grid_size));
    std::random_device random_device;
    std::default_random_engine engine(random_device());
    std::uniform_int_distribution<int> uniform_distribution(1, 10);

    for (std::size_t i = 0; i < x_grid_size; ++i)
    {
        for (std::size_t j = 0; j < y_grid_size; ++j)
        {
            random_generation[i][j] = uniform_distribution(engine) % 3 ? DEAD : LIVE;
        }
    }
    return random_generation;
}

std::size_t game_of_life::get_num_live_(std::size_t x_coord, std::size_t y_coord) const
{
    char num_live = current_generation_[x_coord][y_coord + 1]
                    + current_generation_[x_coord + 1][y_coord]
                    + current_generation_[x_coord][y_coord - 1]
                    + current_generation_[x_coord - 1][y_coord]
                    + current_generation_[x_coord + 1][y_coord + 1]
                    + current_generation_[x_coord + 1][y_coord - 1]
                    + current_generation_[x_coord - 1][y_coord + 1]
                    + current_generation_[x_coord - 1][y_coord - 1];

    if (num_live < 0 || num_live > 8)
    {
        std::cout << int(num_live) << std::endl;
        throw std::logic_error("More than 8 neighbours");
    }

    return static_cast<std::size_t>(num_live);
}