#include <iostream>
#include <mpi.h>

int main(int args, char** argv) {
    MPI_Init(&args, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    printf("Process number: %d; processes: %d", rank, size);
    MPI_Finalize();
    return 0;
}
