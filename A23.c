#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 200

void initialize(double *A) {
    for(int i = 0; i < SIZE; i++)
        A[i] = i * 1.0;
}

void scalar_add_static(double *A, double scalar, int chunk) {

    #pragma omp parallel for schedule(static, chunk)
    for(int i = 0; i < SIZE; i++)
        A[i] += scalar;
}

void scalar_add_dynamic(double *A, double scalar, int chunk) {

    #pragma omp parallel for schedule(dynamic, chunk)
    for(int i = 0; i < SIZE; i++)
        A[i] += scalar;
}

void nowait_demo(double *A, double scalar) {

    #pragma omp parallel
    {
        #pragma omp for nowait
        for(int i = 0; i < SIZE; i++)
            A[i] += scalar;

        printf("Thread %d finished first loop\n",
               omp_get_thread_num());
    }
}

int main() {

    double *A = (double*) malloc(SIZE * sizeof(double));
    int chunks[] = {1, 5, 10, 20, 50};
    int num_chunks = 5;

    printf("\n===== STATIC SCHEDULE ANALYSIS =====\n");

    for(int c = 0; c < num_chunks; c++) {

        initialize(A);
        omp_set_num_threads(1);

        double start = omp_get_wtime();
        scalar_add_static(A, 5.0, chunks[c]);
        double end = omp_get_wtime();

        printf("Chunk Size = %d, Time = %f sec\n",
               chunks[c], end - start);
    }

    printf("\n===== DYNAMIC SCHEDULE ANALYSIS =====\n");

    for(int c = 0; c < num_chunks; c++) {

        initialize(A);
        omp_set_num_threads(1);

        double start = omp_get_wtime();
        scalar_add_dynamic(A, 5.0, chunks[c]);
        double end = omp_get_wtime();

        printf("Chunk Size = %d, Time = %f sec\n",
               chunks[c], end - start);
    }

    printf("\n===== NOWAIT DEMONSTRATION =====\n");
    initialize(A);
    nowait_demo(A, 5.0);

    free(A);

    return 0;
}
