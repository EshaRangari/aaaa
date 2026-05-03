#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

#define TILE_SIZE 16

// G MEMORY
__global__ void matMulGlobal(int *A, int *B, int *C, int N)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < N && col < N)
    {
        int sum = 0;
        for (int k = 0; k < N; k++)
        {
            sum += A[row * N + k] * B[k * N + col];
        }
        C[row * N + col] = sum;
    }
}

// S MEMORY
__global__ void matMulShared(int *A, int *B, int *C, int N)
{
    __shared__ int sA[TILE_SIZE][TILE_SIZE];
    __shared__ int sB[TILE_SIZE][TILE_SIZE];

    int row = blockIdx.y * TILE_SIZE + threadIdx.y;
    int col = blockIdx.x * TILE_SIZE + threadIdx.x;

    int sum = 0;

    for (int t = 0; t < (N + TILE_SIZE - 1) / TILE_SIZE; t++)
    {
        // Load tiles into shared memory
        if (row < N && (t * TILE_SIZE + threadIdx.x) < N)
            sA[threadIdx.y][threadIdx.x] =
                A[row * N + t * TILE_SIZE + threadIdx.x];
        else
            sA[threadIdx.y][threadIdx.x] = 0;

        if (col < N && (t * TILE_SIZE + threadIdx.y) < N)
            sB[threadIdx.y][threadIdx.x] =
                B[(t * TILE_SIZE + threadIdx.y) * N + col];
        else
            sB[threadIdx.y][threadIdx.x] = 0;

        __syncthreads();

        // Multiply tiles
        for (int k = 0; k < TILE_SIZE; k++)
        {
            sum += sA[threadIdx.y][k] * sB[k][threadIdx.x];
        }

        __syncthreads();
    }

    if (row < N && col < N)
        C[row * N + col] = sum;
}

int main()
{
    int N;
    printf("Enter size of matrices (N x N): ");
    scanf("%d", &N);

    size_t size = N * N * sizeof(int);

    int *A = (int *)malloc(size);
    int *B = (int *)malloc(size);
    int *C = (int *)malloc(size);

    printf("Enter %d elements of Matrix A:\n", N * N);
    for (int i = 0; i < N * N; i++)
        scanf("%d", &A[i]);

    printf("Enter %d elements of Matrix B:\n", N * N);
    for (int i = 0; i < N * N; i++)
        scanf("%d", &B[i]);

    int *d_A, *d_B, *d_C;
    cudaMalloc(&d_A, size);
    cudaMalloc(&d_B, size);
    cudaMalloc(&d_C, size);

    cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, size, cudaMemcpyHostToDevice);

    dim3 threads(TILE_SIZE, TILE_SIZE);
    dim3 blocks((N + TILE_SIZE - 1) / TILE_SIZE,
                (N + TILE_SIZE - 1) / TILE_SIZE);

    cudaEvent_t start, stop;
    float timeGlobal, timeShared;

    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    // G TIMING
    cudaEventRecord(start);
    matMulGlobal<<<blocks, threads>>>(d_A, d_B, d_C, N);
    cudaDeviceSynchronize();
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&timeGlobal, start, stop);

    // S TIMING
    cudaEventRecord(start);
    matMulShared<<<blocks, threads>>>(d_A, d_B, d_C, N);
    cudaDeviceSynchronize();
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&timeShared, start, stop);

    cudaMemcpy(C, d_C, size, cudaMemcpyDeviceToHost);

    printf("\nResult Matrix:\n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%d ", C[i * N + j]);
        printf("\n");
    }

    printf("\nGlobal Memory Time: %f ms\n", timeGlobal);
    printf("Shared Memory Time: %f ms\n", timeShared);

    float speedup = timeGlobal / timeShared;
    printf("Speedup: %f\n", speedup);

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    free(A);
    free(B);
    free(C);

    return 0;
}