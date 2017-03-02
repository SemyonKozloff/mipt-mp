#include <boost/mpi.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>

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
    game.launch(20);
    auto result = game.get_current_generation();

    assert(expected == game.get_current_generation());

    return 0;
}