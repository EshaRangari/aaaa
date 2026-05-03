#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Ascending order
int compareAsc(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Descending order
int compareDesc(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int main() {
    int n, i;
    long long minScalar = 0;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int A[n], B[n];

    printf("Enter elements of vector A:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &A[i]);

    printf("Enter elements of vector B:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &B[i]);

    // Sorting (serial part)
    qsort(A, n, sizeof(int), compareAsc);
    qsort(B, n, sizeof(int), compareDesc);

    double start = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp for schedule(static) reduction(+:minScalar) nowait
        for(i = 0; i < n; i++) {
            minScalar += (long long)A[i] * B[i];
        }

        // Ordered example
        #pragma omp for ordered schedule(dynamic)
        for(i = 0; i < n; i++) {
            #pragma omp ordered
            printf("Thread %d processed index %d\n", omp_get_thread_num(), i);
        }
    }

    double end = omp_get_wtime();

    printf("Minimum Scalar Product = %lld\n", minScalar);
    printf("Execution Time = %f seconds\n", end - start);

    return 0;
}
