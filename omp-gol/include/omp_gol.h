#ifndef MIPT_MP_OMP_GOL_H
#define MIPT_MP_OMP_GOL_H

#include <vector>
#include <limits>
#include <iostream>

#include "base_gol.h"

class omp_game_of_life : public game_of_life
{
public:
    explicit omp_game_of_life(const grid_t& init_generation);

    void launch(std::size_t num_generations = DEF_NUM_GENERATIONS_) override;
};

#endif //MIPT_MP_OMP_GOL_H