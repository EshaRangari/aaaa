#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int n = 8;  
    int A[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int sum = 0, final_sum = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(size != 2) {
        if(rank == 0) 
            printf("Please run with 2 processes.\n");
        MPI_Finalize();
        return 0;
    }

    int mid = n / 2;

    if(rank == 0) {
        // P0 sums first half
        printf("Process 0 is calculating sum of first half: ");
        for(int i = 0; i < mid; i++) {
            sum += A[i];
            printf("%d ", A[i]);
        }
        printf("\n Partial sum = %d\n", sum);

        // Receive sum from P1
        int sum_p1;
        MPI_Recv(&sum_p1, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 0 received partial sum %d from Process 1\n", sum_p1);

        final_sum = sum + sum_p1;
        printf("Final sum of array = %d\n", final_sum);
    } 
    else if(rank == 1) {
        // P1 sums second half
        printf("Process 1 is calculating sum of second half: ");
        for(int i = mid; i < n; i++) {
            sum += A[i];
            printf("%d ", A[i]);
        }
        printf("\n Partial sum = %d\n", sum);

        // Send sum to P0
        MPI_Send(&sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
