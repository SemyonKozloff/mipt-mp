#include <boost/mpi.hpp>

#include "mpi_gameoflife.h"

namespace mpi = boost::mpi;

int main()
{
    mpi::environment env;

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

    return 0;
}