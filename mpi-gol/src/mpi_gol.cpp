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
    std::vector<grid_t> grid_chunks;

    if (proc_rank_ == MASTER_PROC_RANK_)
    {
        std::size_t chunk_size = grid.size() / (num_processes_ - 1);
        std::size_t remainder_size = grid.size() % (num_processes_ - 1);

        grid_chunks.emplace_back(); // empty chunk for master process
        for (auto left_it = std::begin(grid), right_it = left_it;
             left_it < std::end(grid);
             left_it = right_it)
        {
            right_it = left_it + chunk_size + (remainder_size > 0 ? 1 : 0);
            if (remainder_size > 0)
            {
                --remainder_size;
            }
            grid_chunks.emplace_back(left_it, right_it);
        }
    }

    grid_t portion;
    mpi::scatter(world_, grid_chunks, portion, MASTER_PROC_RANK_);

    return portion;
}

int mpi_game_of_life::left_neighbour_() const noexcept
{
    return proc_rank_ == 1 ? num_processes_ - 1 : proc_rank_ - 1;
}

int mpi_game_of_life::right_neighbour_() const noexcept
{
    return proc_rank_ ==  num_processes_ - 1 ? 1 : proc_rank_ + 1;
}

game_of_life::grid_t mpi_game_of_life::gather_grid_(const game_of_life::grid_t& local_grid) const
{
    if (proc_rank_ == MASTER_PROC_RANK_)
    {
        std::vector<grid_t> grid_chunks;
        mpi::gather(world_, local_grid, grid_chunks, MASTER_PROC_RANK_);

        grid_t gathered_grid;
        for (const auto& grid : grid_chunks)
        {
            gathered_grid.insert(std::end(gathered_grid), std::cbegin(grid), std::cend(grid));
        }

        return gathered_grid;
    }
    else
    {
        return local_grid;
    }
}

game_of_life::grid_t mpi_game_of_life::get_current_generation()
{
    current_generation_ = gather_grid_(current_generation_);

    return game_of_life::get_current_generation();
}
