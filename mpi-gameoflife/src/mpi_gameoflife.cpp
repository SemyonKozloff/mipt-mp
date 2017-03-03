#include <boost/serialization/vector.hpp>

#include "gameoflife.h"
#include "mpi_gameoflife.h"

mpi_gameoflife::mpi_gameoflife(const gameoflife::grid_t& init_generation)
        : world_(),
          proc_rank_(world_.rank()),
          num_processes_(world_.size())
{
    if (num_processes_ < 3) {
        throw std::invalid_argument("Too few processes");
    }

    generation_counter_ = 0;

    current_generation_ = add_borders_(scatter_grid_(init_generation));

    x_grid_size_ = current_generation_.size();
    y_grid_size_ = current_generation_.front().size();

    if (init_generation.size() < std::size_t(num_processes_)) {
        throw std::invalid_argument("Too small field for such number of process");
    }

    next_generation_ = grid_t(x_grid_size_, row_t(y_grid_size_));
}

void mpi_gameoflife::launch(std::size_t num_generations)
{
    mpi::broadcast(world_, num_generations, MASTER_PROC_RANK_);

    bool is_changed = true;

    for (std::size_t step_counter = 0;
         step_counter < num_generations && is_changed;
         ++step_counter, ++generation_counter_)
    {
        exchange_borders_();

        is_changed = step_();
        is_changed = mpi::all_reduce(world_, is_changed, std::logical_or<bool>());
    }
}

gameoflife::grid_t mpi_gameoflife::scatter_grid_(const gameoflife::grid_t& grid) const
{
    // packing for scattering among processes using mpi_scatter
    std::vector<grid_t> grid_chunks;

    std::size_t chunk_size = grid.size() / num_processes_;
    std::size_t remainder_size = grid.size() % num_processes_;

    for (auto left_it = std::cbegin(grid), right_it = left_it;
         left_it < std::cend(grid);
         left_it = right_it)
    {
        right_it = left_it + chunk_size + (remainder_size > 0 ? 1 : 0);
        if (remainder_size > 0) {
            --remainder_size;
        }
        grid_chunks.emplace_back(left_it, right_it);
    }

    grid_t portion;
    mpi::scatter(world_, grid_chunks, portion, MASTER_PROC_RANK_);

    return portion;
}

gameoflife::grid_t mpi_gameoflife::gather_grid_(const gameoflife::grid_t& local_grid) const
{
    std::vector<grid_t> grid_chunks;
    mpi::gather(world_, local_grid, grid_chunks, MASTER_PROC_RANK_);

    if (proc_rank_ == MASTER_PROC_RANK_) {
        grid_t gathered_grid;
        for (auto&& grid : grid_chunks) {
            gathered_grid.insert(std::end(gathered_grid), std::cbegin(grid), std::cend(grid));
        }

        return gathered_grid;
    }
    else {
        return local_grid;
    }
}

int mpi_gameoflife::left_neighbour_() const noexcept
{
    return proc_rank_ == 0 ? num_processes_ - 1 : proc_rank_ - 1;
}

int mpi_gameoflife::right_neighbour_() const noexcept
{
    return proc_rank_ == num_processes_ - 1 ? 0 : proc_rank_ + 1;
}

gameoflife::grid_t mpi_gameoflife::get_current_generation()
{
    auto gathered_curr_gen = gather_grid_(remove_borders_(current_generation_));

    mpi::broadcast(world_, gathered_curr_gen, MASTER_PROC_RANK_);
    return gathered_curr_gen;
}

void mpi_gameoflife::exchange_borders_()
{
    if (proc_rank_ == 0) {
        world_.send(right_neighbour_(), proc_rank_, *(std::end(current_generation_) - 2));
        world_.recv(right_neighbour_(), right_neighbour_(), current_generation_.back());
    }
    else if (proc_rank_ == num_processes_ - 1) {
        world_.send(left_neighbour_(), proc_rank_, *(std::begin(current_generation_) + 1));
        world_.recv(left_neighbour_(), left_neighbour_(), current_generation_.front());
    }
    else {
        world_.send(left_neighbour_(), proc_rank_, *(std::begin(current_generation_) + 1));
        world_.send(right_neighbour_(), proc_rank_, *(std::end(current_generation_) - 2));

        world_.recv(left_neighbour_(), left_neighbour_(), current_generation_.front());
        world_.recv(right_neighbour_(), right_neighbour_(), current_generation_.back());
    }
}
