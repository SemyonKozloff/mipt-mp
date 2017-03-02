#include <boost/serialization/vector.hpp>
#include <boost/graph/adjacency_list.hpp>

#include "gameoflife.h"
#include "mpi_gameoflife.h"

mpi_gameoflife::mpi_gameoflife(const gameoflife::grid_t& init_generation)
        : world_(),
          proc_rank_(world_.rank()),
          num_processes_(world_.size())
{
    generation_counter_ = 0;

    current_generation_ = add_borders_(scatter_grid_(init_generation));

    x_grid_size_ = current_generation_.size();
    y_grid_size_ = current_generation_.front().size();

    next_generation_ = grid_t(x_grid_size_, row_t(y_grid_size_));
}

void mpi_gameoflife::launch(std::size_t num_generations)
{
    mpi::broadcast(world_, num_generations, MASTER_PROC_RANK_);

    if (proc_rank_ != MASTER_PROC_RANK_)
    {
        for (std::size_t step_counter = 0; step_counter < num_generations; ++step_counter)
        {
            //std::array<mpi::request, 4> requests;

            //std::cout << step_counter << ":" << proc_rank_ << std::endl;
            //display_grid(current_generation_);
            //std::cout.flush();

            if (proc_rank_ == 1)
            {
                world_.send(right_neighbour_(), proc_rank_, *(std::end(current_generation_) - 2));
                world_.recv(right_neighbour_(), right_neighbour_(), current_generation_.back());
            }
            else if (proc_rank_ == num_processes_ - 1)
            {
                world_.send(left_neighbour_(), proc_rank_, *(std::begin(current_generation_) + 1));
                world_.recv(left_neighbour_(), left_neighbour_(), current_generation_.front());
            }
            else
            {
                world_.send(left_neighbour_(), proc_rank_, *(std::begin(current_generation_) + 1));
                world_.send(right_neighbour_(), proc_rank_, *(std::end(current_generation_) - 2));

                world_.recv(left_neighbour_(), left_neighbour_(), current_generation_.front());
                world_.recv(right_neighbour_(), right_neighbour_(), current_generation_.back());
            }

            for (std::size_t i = 1; i < x_grid_size_ - 1; ++i)
            {
                for (std::size_t j = 1; j < y_grid_size_ - 1; ++j)
                {
                    std::size_t num_live = get_num_live_(i, j);

                    if (num_live == 2)
                    {
                        next_generation_[i][j] = current_generation_[i][j];
                    }
                    else if (num_live == 3)
                    {
                        next_generation_[i][j] = LIVE_;
                    }
                    else if (num_live < 2 || num_live > 3)
                    {
                        next_generation_[i][j] = DEAD_;
                    }
                }
            }

            std::swap(current_generation_, next_generation_);
        }
    }
    else
    {
        // visualisation code
        ++generation_counter_;
    }
}

gameoflife::grid_t mpi_gameoflife::scatter_grid_(const gameoflife::grid_t& grid)
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

    return proc_rank_ == MASTER_PROC_RANK_ ? grid : portion;
}

int mpi_gameoflife::left_neighbour_() const noexcept
{
    return proc_rank_ == 1 ? num_processes_ - 1 : proc_rank_ - 1;
}

int mpi_gameoflife::right_neighbour_() const noexcept
{
    return proc_rank_ == num_processes_ - 1 ? 1 : proc_rank_ + 1;
}

gameoflife::grid_t mpi_gameoflife::gather_grid_(const gameoflife::grid_t& local_grid) const
{
    std::vector<grid_t> grid_chunks;
    mpi::gather(world_, local_grid, grid_chunks, MASTER_PROC_RANK_);

    if (proc_rank_ == MASTER_PROC_RANK_)
    {
        grid_t gathered_grid;
        for (auto it = std::begin(grid_chunks) + 1; it != std::end(grid_chunks); ++it)
        {
            gathered_grid.insert(std::end(gathered_grid), std::cbegin(*it), std::cend(*it));
        }

        return gathered_grid;
    }
    else
    {
        return local_grid;
    }
}

gameoflife::grid_t mpi_gameoflife::get_current_generation()
{
    world_.barrier();
    auto gathered_curr_gen = gather_grid_(remove_borders_(current_generation_));

    mpi::broadcast(world_, gathered_curr_gen, MASTER_PROC_RANK_);
    return gathered_curr_gen;
}