#ifndef MIPT_MP_MPI_GOL_H
#define MIPT_MP_MPI_GOL_H

#include <boost/mpi.hpp>

#include "gameoflife.h"

namespace mpi = boost::mpi;

class mpi_gameoflife final : public gameoflife
{
public:
    mpi_gameoflife(const grid_t& init_generation);

    void launch(std::size_t num_generations = DEF_NUM_GENERATIONS_) override;

    grid_t get_current_generation() override;

private:
    grid_t scatter_grid_(const grid_t& grid);
    grid_t gather_grid_(const grid_t& local_grid) const;

    int left_neighbour_() const noexcept;
    int right_neighbour_() const noexcept;

    mutable mpi::communicator world_;
    int proc_rank_;
    int num_processes_;

    static const int MASTER_PROC_RANK_ = 0;
};

#endif //MIPT_MP_MPI_GOL_H
