#ifndef MIPT_MP_BASE_GOL_H
#define MIPT_MP_BASE_GOL_H

#include <vector>
#include <limits>
#include <iostream>

class gameoflife
{
public:
    using state_t = char;
    using row_t = std::vector<state_t>;
    using grid_t = std::vector<row_t>;

    gameoflife() = default;
    explicit gameoflife(const grid_t& init_generation);

    virtual void launch(std::size_t num_generations = DEF_NUM_GENERATIONS_);

    virtual grid_t get_current_generation();
    virtual std::size_t get_num_generations() const noexcept;

    static grid_t get_random_generation(std::size_t x_grid_size,
                                        std::size_t y_grid_size);

protected:
    // return the number of alive neighbours
    std::size_t get_num_live_(std::size_t x, std::size_t y) const;
    grid_t add_borders_(const grid_t& grid);
    grid_t remove_borders_(const grid_t& grid);

    bool step_();

    std::size_t generation_counter_;

    grid_t current_generation_;

    std::size_t x_grid_size_;
    std::size_t y_grid_size_;

    grid_t next_generation_;

    static const state_t LIVE_ = 1;
    static const state_t DEAD_ = 0;

    static const std::size_t DEF_NUM_GENERATIONS_ =
            std::numeric_limits<std::size_t>::max();
};

#endif //MIPT_MP_BASE_GOL_H
