#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void initialize(double *A, double *B, int n) {
    for(int i = 0; i < n*n; i++) {
        A[i] = rand() % 100;
        B[i] = rand() % 100;
    }
}

void matrix_add(double *A, double *B, double *C, int n) {

    #pragma omp parallel for schedule(static)
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            C[i*n + j] = A[i*n + j] + B[i*n + j];
        }
    }
}

int main() {

    int sizes[] = {250, 500, 750, 1000, 2000};
    int threads[] = {1, 2, 4, 8};

    int num_sizes = 5;
    int num_threads = 4;

    printf("\n===== MATRIX ADDITION PERFORMANCE ANALYSIS =====\n\n");

    for(int s = 0; s < num_sizes; s++) {

        int n = sizes[s];
        double baseline_time = 0;

        printf("Matrix Size: %d x %d\n", n, n);
        printf("Threads\tTime (sec)\tSpeedup\n");

        for(int t = 0; t < num_threads; t++) {

            omp_set_num_threads(threads[t]);

            double *A = (double*) malloc(n*n*sizeof(double));
            double *B = (double*) malloc(n*n*sizeof(double));
            double *C = (double*) malloc(n*n*sizeof(double));

            initialize(A, B, n);

            double start = omp_get_wtime();
            matrix_add(A, B, C, n);
            double end = omp_get_wtime();

            double time = end - start;

            if(threads[t] == 1)
                baseline_time = time;

            double speedup = baseline_time / time;

            printf("%d\t%.6f\t%.2f\n",
                   threads[t], time, speedup);

            free(A);
            free(B);
            free(C);
        }

        printf("\n");
    }

    return 0;
}

