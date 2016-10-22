#include <vector>
#include <iostream>

#include <omp.h>

#include "omp-gol.h"

const std::size_t X_SIZE = 5;
const std::size_t Y_SIZE = 5;
const std::size_t NUM_GENERATIONS = 20;

int main()
{
    auto random_generation = game_of_life::get_random_generation(X_SIZE, Y_SIZE);

    decltype(random_generation) custom_generation = {{0, 0, 1, 0, 0, 0},
                                                     {0, 0, 0, 1, 0, 0},
                                                     {0, 1, 1, 1, 0, 0},
                                                     {0, 0, 0, 0, 0, 0},
                                                     {0, 0, 0, 0, 0, 0}};
    game_of_life game(custom_generation);
    game.launch(NUM_GENERATIONS);

    return 0;
}