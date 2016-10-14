#include <mpi.h>

#include <iostream>

int main(int argc, char* argv[])
{
    int i = MPI_Init(&argc, &argv);
    std::cout << i << std::endl;
    i = MPI_Finalize();
    std::cout << i << std::endl;
    return 0;
}
