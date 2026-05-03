#include <stdio.h>
#include <stdlib.h>

// Function to compare for ascending order
int compareAsc(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Function to compare for descending order
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

    // Sort vectors
    qsort(A, n, sizeof(int), compareAsc);
    qsort(B, n, sizeof(int), compareDesc);

    // Compute minimum scalar product
    for(i = 0; i < n; i++)
        minScalar += (long long)A[i] * B[i];

    printf("Minimum Scalar Product = %lld\n", minScalar);

    return 0;
}
