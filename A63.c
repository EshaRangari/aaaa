#include <mpi.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int msg = 100;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(size < 2) {
        if(rank == 0)
            printf("Please run with at least 2 processes\n");
        MPI_Finalize();
        return 0;
    }

    if(rank == 0) {
        printf("Process 0 ready to send to Process 1\n");
        sleep(1); // Simulate delay
        printf("Process 0 sending message to Process 1 (blocking send)\n");
        MPI_Send(&msg, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 waiting to receive message from Process 1\n");
        MPI_Recv(&msg, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 0 received message from Process 1\n");
    } 
    else if(rank == 1) {
        printf("Process 1 ready to send to Process 0\n");
        sleep(1); // Simulate delay
        printf("Process 1 sending message to Process 0 (blocking send)\n");
        MPI_Send(&msg, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        printf("Process 1 waiting to receive message from Process 0\n");
        MPI_Recv(&msg, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received message from Process 0\n");
    }

    MPI_Finalize();
    return 0;
}
