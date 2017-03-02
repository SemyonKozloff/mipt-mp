#ifndef MIPT_MP_OMP_GOL_H
#define MIPT_MP_OMP_GOL_H

#include <vector>
#include <limits>
#include <iostream>

#include "gameoflife.h"

class omp_gameoflife : public gameoflife
{
public:
    explicit omp_gameoflife(const grid_t& init_generation);

    void launch(std::size_t num_generations = DEF_NUM_GENERATIONS_) override;
};

#endif //MIPT_MP_OMP_GOL_H