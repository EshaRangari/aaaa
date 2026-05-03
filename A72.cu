#include <stdio.h>

__global__ void hello() {
    int id = threadIdx.x;   // Thread ID inside block
    printf("Hello World from Thread %d\n", id);
}

int main() {

    hello<<<1, 5>>>();

    cudaDeviceSynchronize();

    return 0;
}