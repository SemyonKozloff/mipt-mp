#include <stdbool.h>
#include <stdio.h>

#include <omp.h>

#define OMP_NUM_THREADS 4



int main(int argc, char* argv[])
{
    printf("%ld\n", sizeof(bool));
    return 0;
}
