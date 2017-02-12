#ifndef MIPT_MP_MPI_GOL_H
#define MIPT_MP_MPI_GOL_H

#include <boost/mpi.hpp>

#include "base_gol.h"

namespace mpi = boost::mpi;

void display_grid(const auto& grid)
{
    for (auto&& row : grid)
    {
        for (auto&& cell : row)
        {
            std::cout << std::size_t(cell) << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
}

class mpi_game_of_life final : public game_of_life
{
public:
    mpi_game_of_life(const grid_t& init_generation);

    void launch(std::size_t num_generations = DEF_NUM_GENERATIONS_) override;

private:
    grid_t scatter_grid_(const grid_t& grid);
    grid_t gather_grid_(const grid_t& local_grid) const;

    int left_neighbour_() const noexcept;
    int right_neighbour_() const noexcept;

    mpi::communicator world_;
    int proc_rank_;
    int num_processes_;

    static const int MASTER_PROC_RANK_ = 0;
};

#endif //MIPT_MP_MPI_GOL_H
