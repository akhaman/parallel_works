#include <iostream>
#include <mpi.h>

int main(int args, char** argv) {
    MPI_Init(&args, &argv);

    const int root = 0;
    const int messageSize = 10;
    int sendBuffer[messageSize];
    int worldRank, worldSize, result;
    int intermediateResult = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &worldRank);
    MPI_Comm_size(MPI_COMM_WORLD, &worldSize);

    const int sendCount = messageSize / worldSize;
    int receiveBuffer[sendCount];

    if (worldRank == root) for (int &i: sendBuffer) i = rand();

    MPI_Scatter(sendBuffer,
                sendCount,
                MPI_INT,
                receiveBuffer,
                sendCount,
                MPI_INT,
                root,
                MPI_COMM_WORLD);

    for (int i : receiveBuffer) {
        intermediateResult += abs(i);
    }
    MPI_Reduce(&intermediateResult,
               &result,
               1,
               MPI_INT,
               MPI_SUM,
               root,
               MPI_COMM_WORLD);

    if (worldRank == root) {
        printf("result = %d", result);
    }

    MPI_Finalize();
    return 0;
}