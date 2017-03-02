#include <cstdlib>
#include <random>
#include <stdexcept>
#include <iostream>
#include <lcms2.h>

#include "utils.h"
#include "gameoflife.h"

const gameoflife::state_t gameoflife::DEAD_;
const gameoflife::state_t gameoflife::LIVE_;

gameoflife::gameoflife(const gameoflife::grid_t& init_generation)
        : generation_counter_(0),
          current_generation_(add_borders_(init_generation)),
          x_grid_size_(current_generation_.size()),
          y_grid_size_(current_generation_.front().size()),
          next_generation_(x_grid_size_, row_t(y_grid_size_))
{ }

void gameoflife::launch(std::size_t num_generations)
{
    bool is_changed = true;

    for (std::size_t step_counter = 0;
         step_counter < num_generations && is_changed;
         ++step_counter, ++generation_counter_)
    {
        is_changed = false;
        // avoiding borders
        for (std::size_t x = 1; x < x_grid_size_ - 1; ++x)
        {
            for (std::size_t y = 1; y < y_grid_size_ - 1; ++y)
            {
                std::size_t num_live = get_num_live_(x, y);

                if (num_live == 2)
                {
                    next_generation_[x][y] = current_generation_[x][y];
                }
                else if (num_live == 3)
                {
                    next_generation_[x][y] = LIVE_;
                }
                else if (num_live < 2 || num_live > 3)
                {
                    next_generation_[x][y] = DEAD_;
                }

                if (current_generation_[x][y] != next_generation_[x][y])
                {
                    is_changed = true;
                }
            }
        }

        std::swap(current_generation_, next_generation_);
    }
}

gameoflife::grid_t gameoflife::get_current_generation()
{
    return remove_borders_(current_generation_);
}

gameoflife::grid_t gameoflife::get_random_generation(std::size_t x_grid_size,
                                                     std::size_t y_grid_size)
{
    grid_t random_generation(x_grid_size, row_t(y_grid_size));
    std::random_device random_device;
    std::default_random_engine engine(random_device());
    std::uniform_int_distribution<std::size_t> uniform_distribution(1, 10);

    for (std::size_t i = 0; i < x_grid_size; ++i)
    {
        for (std::size_t j = 0; j < y_grid_size; ++j)
        {
            random_generation[i][j] = uniform_distribution(engine) % 3 ? DEAD_ : LIVE_;
        }
    }
    return random_generation;
}

std::size_t gameoflife::get_num_live_(std::size_t x, std::size_t y) const
{
    char num_live = current_generation_[x][y + 1]
                    + current_generation_[x + 1][y]
                    + current_generation_[x][y - 1]
                    + current_generation_[x - 1][y]
                    + current_generation_[x + 1][y + 1]
                    + current_generation_[x + 1][y - 1]
                    + current_generation_[x - 1][y + 1]
                    + current_generation_[x - 1][y - 1];

    if (num_live < 0 || num_live > 8)
    {
        throw std::logic_error("More than 8 neighbours");
    }

    return static_cast<std::size_t>(num_live);
}

std::size_t gameoflife::get_num_generations() const noexcept
{
    return generation_counter_;
}

gameoflife::grid_t gameoflife::add_borders_(const gameoflife::grid_t& grid)
{
    grid_t temp_grid = grid;

    for (auto&& row : temp_grid)
    {
        row.insert(std::begin(row), DEAD_);
        row.push_back(DEAD_);
    }
    temp_grid.insert(std::begin(temp_grid),
                     row_t(grid.front().size() + 2, DEAD_));
    temp_grid.push_back(row_t(grid.front().size() + 2, DEAD_));

    return temp_grid;
}

gameoflife::grid_t gameoflife::remove_borders_(const gameoflife::grid_t& grid)
{
    auto temp_grid = grid;

    // removing borders
    temp_grid.erase(std::begin(temp_grid));
    temp_grid.pop_back();
    for (auto&& row : temp_grid)
    {
        row.erase(std::begin(row));
        row.pop_back();
    }

    return temp_grid;
}
