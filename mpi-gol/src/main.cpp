#include <boost/mpi.hpp>

#include "mpi_gol.h"

namespace mpi = boost::mpi;

int main()
{
    mpi::environment environment;
    auto random_generation = mpi_game_of_life::get_random_generation(10, 10);


    mpi_game_of_life gol(random_generation);
    return 0;
}