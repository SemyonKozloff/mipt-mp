#include <boost/mpi.hpp>

#include "mpi_gameoflife.h"

namespace mpi = boost::mpi;

int main()
{
    mpi::environment env;
/*
    // test correctness
    std::vector<std::vector<char>> input =
            {{0, 0, 1, 0, 0, 0},
             {0, 0, 0, 1, 0, 0},
             {0, 1, 1, 1, 0, 0},
             {0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0}};

    std::vector<std::vector<char>> expected =
            {{0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 1, 1},
             {0, 0, 0, 0, 1, 1}};

    mpi_gameoflife game(input);
    game.launch();
    auto result = game.get_current_generation();

    assert(expected == game.get_current_generation());
*/
    // test performance
    const std::size_t x_size = 1000, y_size = 1000, num_steps = 100;
    mpi_gameoflife big_game(gameoflife::get_random_generation(x_size, y_size));

    mpi::timer timer;
    big_game.launch(num_steps);
    std::cout << timer.elapsed() << std::endl;

    return 0;
}