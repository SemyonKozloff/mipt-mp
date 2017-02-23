#include <boost/serialization/vector.hpp>

#include "base_gol.h"
#include "mpi_gol.h"


mpi_game_of_life::mpi_game_of_life(const game_of_life::grid_t& init_generation)
        : world_(),
          proc_rank_(world_.rank()),
          num_processes_(world_.size())
{
    generation_counter_ = 0;

    current_generation_ = add_borders_(scatter_grid_(init_generation));
    x_grid_size_ = current_generation_.size();
    y_grid_size_ = current_generation_.front().size();

    next_generation_ = std::move(grid_t(x_grid_size_, row_t(y_grid_size_)));
}


void mpi_game_of_life::launch(std::size_t num_generations)
{
    mpi::broadcast(world_, num_generations, MASTER_PROC_RANK_);

    if (proc_rank_ != MASTER_PROC_RANK_)
    {
        for (std::size_t step_counter = 0; step_counter < num_generations; ++step_counter)
        {
            world_.send(left_neighbour_(), proc_rank_, current_generation_.front());
            world_.send(right_neighbour_(), proc_rank_, current_generation_.back());

            row_t left_border, right_border;
            world_.recv(left_neighbour_(), left_neighbour_(), left_border);
            world_.recv(right_neighbour_(), right_neighbour_(), right_border);

            current_generation_.front() = std::move(left_border);
            current_generation_.back() = std::move(right_border);

            game_of_life::launch(1);
        }
    }
    else
    {
        ++generation_counter_;
    }


}

game_of_life::grid_t mpi_game_of_life::scatter_grid_(const game_of_life::grid_t& grid)
{
    // packing for scattering among processes using mpi_scatter
    std::vector<grid_t> grid_pack;
    if (proc_rank_ == MASTER_PROC_RANK_)
    {
        grid_pack.emplace_back();
        std::size_t portion_size = grid.size() / (num_processes_ - 1);

        auto left_it = std::begin(grid);
        for (auto right_it = std::begin(grid) + portion_size;
             right_it <= std::end(grid);
             right_it = std::max(right_it + portion_size, std::end(grid)))
        {
            grid_pack.emplace_back(left_it, right_it);
            left_it = right_it + 1;
        }
    }

    grid_t portion_generation;
    mpi::scatter(world_, grid_pack, portion_generation, MASTER_PROC_RANK_);

    return portion_generation;
}

int mpi_game_of_life::left_neighbour_() const noexcept
{
    return proc_rank_ == 1 ? world_.size() - 1 : proc_rank_ - 1;
}

int mpi_game_of_life::right_neighbour_() const noexcept
{
    return proc_rank_ == world_.size() - 1 ? 1 : proc_rank_ + 1;
}

game_of_life::grid_t mpi_game_of_life::gather_grid_(const game_of_life::grid_t& local_grid) const
{
    if (proc_rank_ == MASTER_PROC_RANK_)
    {
        std::vector<grid_t> grid_pack;
        mpi::gather(world_, local_grid, grid_pack, MASTER_PROC_RANK_);

        grid_t gathered_grid;
        for (const auto& grid : grid_pack)
        {
            gathered_grid.insert(std::end(gathered_grid), std::cbegin(grid), std::cend(grid) - 1);
        }
        gathered_grid.emplace_back(gathered_grid.front().size());

        return gathered_grid;
    }
    else
    {
        return local_grid;
    }
}
