#include <iostream>
#include <mpi.h>
#include <sstream>

void handleSending(int size, int currentRank) {
    const int receiversCount = size - 1;

    if (receiversCount < 1) {
        return;
    }

    const int messageSize = 10;
    const int message[messageSize] = {0,1,2,3,4,5,6,7,8,9};

    int receiver = -1;

    while (receiver < receiversCount) {
        receiver++;

        if (receiver == currentRank) {
            continue;
        }

        MPI_Send(message, messageSize, MPI_INT, receiver, 0, MPI_COMM_WORLD);
    }
}

void handleReceiving(int currentRank) {
    int messageSize;
    MPI_Status status;

    MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    MPI_Get_count(&status, MPI_INT, &messageSize);

    int messageBuffer[messageSize];

    MPI_Recv(messageBuffer,
            messageSize,
            MPI_INT,
            MPI_ANY_SOURCE,
            MPI_ANY_TAG,
            MPI_COMM_WORLD,
            MPI_STATUS_IGNORE);

    std::stringstream ss;
    ss << "Process #" << currentRank << " received: ";

    for (int i = 0; i < messageSize; i++) {
        ss << messageBuffer[i] << " ";
    }

    std::cout << ss.str() << "\n";
}

int main(int args, char** argv) {
    MPI_Init(&args, &argv);
    int size, rank;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    rank == 1 ? handleSending(size, rank) : handleReceiving(rank);

    MPI_Finalize();
    return 0;
}