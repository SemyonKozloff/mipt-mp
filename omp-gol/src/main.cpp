#include <vector>
#include <iostream>

#include <omp.h>

#include "omp-gol.h"

const std::size_t X_SIZE = 10;
const std::size_t Y_SIZE = 10;
const std::size_t NUM_GENERATIONS = 1;

int main()
{
    auto random_generation = game_of_life::get_random_generation(X_SIZE, Y_SIZE);

    game_of_life game(random_generation);
    game.launch(NUM_GENERATIONS);


    return 0;
}