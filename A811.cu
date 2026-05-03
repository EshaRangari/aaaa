#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

// CUDA Kernel
__global__ void vectorAdd(int *A, int *B, int *C, int n) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < n)
        C[i] = A[i] + B[i];
}

int main() {

    int n;
    printf("Enter size of vectors: ");
    scanf("%d", &n);

    size_t size = n * sizeof(int);

    // Allocate host memory
    int *A = (int*)malloc(size);
    int *B = (int*)malloc(size);
    int *C = (int*)malloc(size);

    printf("Enter elements of vector A:\n");
    for(int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    printf("Enter elements of vector B:\n");
    for(int i = 0; i < n; i++)
        scanf("%d", &B[i]);

    // Allocate device memory
    int *d_A, *d_B, *d_C;
    cudaMalloc(&d_A, size);
    cudaMalloc(&d_B, size);
    cudaMalloc(&d_C, size);

    cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, size, cudaMemcpyHostToDevice);

    int threads = 256;
    int blocks = (n + threads - 1) / threads;

    // Timing variables
    cudaEvent_t start, stop;
    float time;

    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaEventRecord(start);

    vectorAdd<<<blocks, threads>>>(d_A, d_B, d_C, n);

    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    cudaEventElapsedTime(&time, start, stop);

    cudaMemcpy(C, d_C, size, cudaMemcpyDeviceToHost);

    printf("\nResult Vector:\n");
    for(int i = 0; i < n; i++)
        printf("%d ", C[i]);

    printf("\nExecution Time: %f ms\n", time);

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
    free(A);
    free(B);
    free(C);

    return 0;
}