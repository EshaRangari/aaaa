#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

//global
__global__ void vecMatGlobal(int *V, int *M, int *R, int N)
{
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (col < N)
    {
        int sum = 0;
        for (int row = 0; row < N; row++)
        {
            sum += V[row] * M[row * N + col];
        }
        R[col] = sum;
    }
}

//SHARED MEMORY
__global__ void vecMatShared(int *V, int *M, int *R, int N)
{
    extern __shared__ int sV[];

    int tid = threadIdx.x;
    int col = blockIdx.x * blockDim.x + tid;

    // Proper loading of vector into shared memory
    for (int i = tid; i < N; i += blockDim.x)
    {
        sV[i] = V[i];
    }

    __syncthreads();

    if (col < N)
    {
        int sum = 0;
        for (int row = 0; row < N; row++)
        {
            sum += sV[row] * M[row * N + col];
        }
        R[col] = sum;
    }
}

int main()
{
    int N;
    printf("Enter size of matrix (N x N): ");
    scanf("%d", &N);

    size_t vecSize = N * sizeof(int);
    size_t matSize = N * N * sizeof(int);

    int *V = (int *)malloc(vecSize);
    int *M = (int *)malloc(matSize);
    int *R = (int *)malloc(vecSize);

    printf("Enter %d elements of vector:\n", N);
    for (int i = 0; i < N; i++)
        scanf("%d", &V[i]);

    printf("Enter %d elements of matrix:\n", N * N);
    for (int i = 0; i < N * N; i++)
        scanf("%d", &M[i]);

    int *d_V, *d_M, *d_R;
    cudaMalloc(&d_V, vecSize);
    cudaMalloc(&d_M, matSize);
    cudaMalloc(&d_R, vecSize);

    cudaMemcpy(d_V, V, vecSize, cudaMemcpyHostToDevice);
    cudaMemcpy(d_M, M, matSize, cudaMemcpyHostToDevice);

    int threads = 256;
    int blocks = (N + threads - 1) / threads;

    cudaEvent_t start, stop;
    float timeGlobal, timeShared;

    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    //GLOBALTime
    cudaEventRecord(start);
    vecMatGlobal<<<blocks, threads>>>(d_V, d_M, d_R, N);
    cudaDeviceSynchronize();
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&timeGlobal, start, stop);

    //  SHARED Time
    cudaEventRecord(start);
    vecMatShared<<<blocks, threads, N * sizeof(int)>>>(d_V, d_M, d_R, N);
    cudaDeviceSynchronize();
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&timeShared, start, stop);

    cudaMemcpy(R, d_R, vecSize, cudaMemcpyDeviceToHost);


    printf("\nCorrect Result Vector:\n");
    for (int i = 0; i < N; i++)
        printf("%d ", R[i]);

    printf("\n\nGlobal Memory Time: %f ms\n", timeGlobal);
    printf("Shared Memory Time: %f ms\n", timeShared);

    float speedup = timeGlobal / timeShared;
    printf("Speedup: %f\n", speedup);

    cudaFree(d_V);
    cudaFree(d_M);
    cudaFree(d_R);

    free(V);
    free(M);
    free(R);

    return 0;
}