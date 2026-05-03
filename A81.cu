#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

// CUDA Kernel
__global__ void vectorScalarAdd(int *A, int scalar, int *C, int n) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < n)
        C[i] = A[i] + scalar;
}

int main() {

    int n;
    printf("Enter size of vector: ");
    scanf("%d", &n);

    int scalar;
    printf("Enter scalar value: ");
    scanf("%d", &scalar);

    size_t size = n * sizeof(int);

    // Allocate host memory
    int *A = (int*)malloc(size);
    int *C = (int*)malloc(size);

    printf("Enter %d elements:\n", n);
    for(int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    // Allocate device memory
    int *d_A, *d_C;
    cudaMalloc(&d_A, size);
    cudaMalloc(&d_C, size);

    cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice);

    int threads = 256;
    int blocks = (n + threads - 1) / threads;

    // Timing variables
    cudaEvent_t start, stop;
    float time;

    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaEventRecord(start);

    vectorScalarAdd<<<blocks, threads>>>(d_A, scalar, d_C, n);

    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    cudaEventElapsedTime(&time, start, stop);

    cudaMemcpy(C, d_C, size, cudaMemcpyDeviceToHost);

    printf("\nResult:\n");
    for(int i = 0; i < n; i++)
        printf("%d ", C[i]);

    printf("\nExecution Time: %f ms\n", time);

    cudaFree(d_A);
    cudaFree(d_C);
    free(A);
    free(C);

    return 0;
}