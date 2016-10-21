#ifndef MIPT_MP_OMP_GOL_H
#define MIPT_MP_OMP_GOL_H

#include <vector>
#include <limits>

enum class state
{
    alive = 1,
    dead = 0
};

class game_of_life
{
    using grid_t = std::vector<std::vector<state>>;

public:
    void game_of_life(std::size_t x_grid_size, std::size_t y_grid_size,
                      const grid_t& init_generation = get_random_generation());

    grid_t get_random_generation() const;

    void launch(std::size_t num_generations = DEF_NUM_GENERATIONS_);

private:
    grid_t current_generation_;
    grid_t next_generation_;

    std::size_t x_grid_size_;
    std::size_t y_grid_size_;

    std::size_t generation_counter_;

    const DEF_NUM_GENERATIONS_ = std::numeric_limits<std::size_t>::max();
};

#endif