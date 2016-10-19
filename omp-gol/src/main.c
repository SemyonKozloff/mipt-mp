#include <stdbool.h>
#include <stdio.h>

#include <omp.h>

#include "omp-gol.h"

#define OMP_NUM_THREADS 4

int main(int argc, char* argv[])
{
    printf("%d", omp_get_max_threads());
    //launch_game(10, 10, 20);
    //char **generation = alloc_grid(10, 10);
    //set_init_generation(10, 10, generation);
    //display_grid(10, 10, generation);
    return 0;
}
