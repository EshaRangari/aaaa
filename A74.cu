#include <stdio.h>


__global__ void hello2D() {

    int tx = threadIdx.x;
    int ty = threadIdx.y;

    int bx = blockIdx.x;
    int by = blockIdx.y;

    printf("Hello World from Block(%d,%d) Thread(%d,%d)\n",
           bx, by, tx, ty);
}

int main() {

    // Define 2D blocks and 2D threads
    dim3 blocks(2,2);      // 2x2 blocks
    dim3 threads(3,3);     // 3x3 threads per block

    hello2D<<<blocks, threads>>>();

    cudaDeviceSynchronize();

    return 0;
}