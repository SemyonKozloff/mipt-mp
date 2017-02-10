#ifndef MPI_GOL_MPI_GOL_H
#define MPI_GOL_MPI_GOL_H

#include "base_gol.h"

class mpi_game_of_life final : public game_of_life
{
public:
    mpi_game_of_life(int* argc_ptr, char*** argv_ptr,
                     const grid_t& init_generation);

    void launch(std::size_t num_generations = DEF_NUM_GENERATIONS_);

private:
    int* argc_ptr_;
    char*** argv_ptr_;

    int proc_id_;

    static const int MASTER_PROC_ID_ = 0;
};

#endif //MIPT_MP_MPI_GOL_H
