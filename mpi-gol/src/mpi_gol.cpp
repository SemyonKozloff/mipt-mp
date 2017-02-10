#include <mpi.h>

#include "base_gol.h"
#include "mpi_gol.h"

mpi_game_of_life::mpi_game_of_life(int* argc_ptr, char*** argv_ptr,
                                   const grid_t& init_generation)
        : argc_ptr_(argc_ptr),
          argv_ptr_(argv_ptr)
{
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_id_);

}

void mpi_game_of_life::launch(size_t num_generations)
{

}
