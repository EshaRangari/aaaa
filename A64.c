#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int send_data, recv_data;
    int next, prev;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    next = (rank + 1) % size;         // Right neighbor
    prev = (rank - 1 + size) % size;  // Left neighbor

    send_data = rank * 10;

    // Send to next, receive from previous (blocking)
    MPI_Send(&send_data, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
    MPI_Recv(&recv_data, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    printf("Process %d sent %d to Process %d and received %d from Process %d\n",
           rank, send_data, next, recv_data, prev);

    MPI_Finalize();
    return 0;
}
