#include <iostream>
#include <mpi.h>

int main(int args, char** argv) {
    MPI_Init(&args, &argv);
    MPI_Status status;
    int rank, size;
    const int arraySize = 10;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0) {
        int a[arraySize];
        for (int i = 0; i < arraySize; i++) {
            a[i] = rand();
        }
        MPI_Send(a, arraySize, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }

    if(rank == 1) {
        int a[arraySize];
        MPI_Recv(a, arraySize, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

        for (int i = 0; i < arraySize; i++) {
            std::cout << a[i] << " ";
        }
    }

    MPI_Finalize();
    return 0;
}