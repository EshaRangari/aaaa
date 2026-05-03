#include <stdio.h>
#include <omp.h>

int main()
{
    int sum = 0;

    double start, end;

    start = omp_get_wtime();

    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int square = id * id;

        printf("Thread ID: %d, Square: %d\n", id, square);

        #pragma omp atomic
        sum += square;
    }

    end = omp_get_wtime();

    printf("\nSum of squares of thread IDs = %d\n", sum);

    printf("\nStart Time : %f\n", start);
    printf("End Time   : %f\n", end);
    printf("Execution Time : %f\n", end-start);

    return 0;
}
