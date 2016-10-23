#ifndef MIPT_MP_OMP_GOL_H
#define MIPT_MP_OMP_GOL_H

#include <vector>
#include <limits>
#include <iostream>

class game_of_life
{
    using state_t = char;
    using row_t = std::vector<state_t>;
    using grid_t = std::vector<row_t>;

public:
    game_of_life(const grid_t& init_generation);

    void launch(std::size_t num_generations = DEF_NUM_GENERATIONS_);

    grid_t get_current_generation() const;
    std::size_t get_num_generations() const noexcept;

    static grid_t get_random_generation(std::size_t x_grid_size,
                                        std::size_t y_grid_size);

private:
    // return the number of alive neighbours
    std::size_t get_num_live_(std::size_t x_coord, std::size_t y_coord) const;

    std::size_t generation_counter_;

    std::size_t x_grid_size_;
    std::size_t y_grid_size_;

    grid_t current_generation_;
    grid_t next_generation_;

    static const state_t LIVE_ = 1;
    static const state_t DEAD_ = 0;

    static const std::size_t DEF_NUM_GENERATIONS_ =
            std::numeric_limits<std::size_t>::max();
};

void display_grid(const auto &grid)
{
    for (auto&& row : grid)
    {
        for (auto&& cell : row)
        {
            std::cout << std::size_t(cell) << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

#endif