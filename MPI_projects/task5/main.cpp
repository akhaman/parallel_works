#include <mpi.h>
#include <iostream>

int main(int args, char** argv) {
    MPI_Init(&args, &argv);
    const int rootRank = 0, vectorLength = 10;
    int worldRank, worldSize, result;
    int intermediateResult = 0;
    int vectorA[vectorLength], vectorB[vectorLength];

    MPI_Comm_rank(MPI_COMM_WORLD, &worldRank);
    MPI_Comm_size(MPI_COMM_WORLD, &worldSize);

    if (worldRank == rootRank) {
        for (int i = 0; i < vectorLength; i++) {
            vectorA[i] = i;
            vectorB[i] = i;
        }
    }

    const int receiveLength = vectorLength / worldSize;
    int receiveA[receiveLength];
    int receiveB[receiveLength];

    MPI_Scatter(vectorA,
                receiveLength,
                MPI_INT,
                receiveA,
                receiveLength,
                MPI_INT,
                rootRank,
                MPI_COMM_WORLD);

    MPI_Scatter(vectorB,
                receiveLength,
                MPI_INT,
                receiveB,
                receiveLength,
                MPI_INT,
                rootRank,
                MPI_COMM_WORLD);

    for (int i = 0; i < receiveLength; i++) {
        intermediateResult += receiveA[i] * receiveB[i];
    }

    MPI_Reduce(&intermediateResult,
               &result,
               1,
               MPI_INT,
               MPI_SUM,
               rootRank,
               MPI_COMM_WORLD);

    if (worldRank == rootRank) {
        printf("result = %d", result);
    }

    MPI_Finalize();
    return 0;
}
