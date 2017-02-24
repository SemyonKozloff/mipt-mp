#include <boost/mpi.hpp>
#include <boost/serialization/vector.hpp>

#include "mpi_gol.h"

namespace mpi = boost::mpi;



int main()
{
    mpi::environment environment;
    mpi::communicator world;


    std::vector<std::vector<int>> chunks;

    std::vector<int> message;

    if (world.rank() == 0)
    {
        std::vector<int> vector(100, world.rank());

        std::size_t chunk_size = vector.size() / (world.size() - 1);
        std::size_t remainder_size = vector.size() % (world.size() - 1);

        chunks.emplace_back();
        for (auto left_it = std::begin(vector), right_it = left_it;
             left_it < std::end(vector);
             left_it = right_it)
        {
            right_it = left_it + chunk_size + (remainder_size > 0 ? 1 : 0);
            if (remainder_size > 0)
            {
                --remainder_size;
            }
            chunks.emplace_back(left_it, right_it);
        }
    }

    mpi::scatter(world, chunks, message, 0);

    for (auto& x : message)
    {
        x += world.rank();
    }

    std::copy(std::begin(message), std::end(message), std::ostream_iterator<int>(std::cout, " "));
    std::cout << message.size() << std::endl;

    return 0;
}