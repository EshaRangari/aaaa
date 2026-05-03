#include <stdio.h>

__global__ void hello() {

    int thread_id = threadIdx.x;     // Thread inside block
    int block_id  = blockIdx.x;      // Block number

    int global_id = blockIdx.x * blockDim.x + threadIdx.x;

    printf("Hello World from Block %d, Thread %d (Global ID %d)\n",
           block_id, thread_id, global_id);
}

int main() {

    hello<<<3,4>>>();

    cudaDeviceSynchronize();

    return 0;
}