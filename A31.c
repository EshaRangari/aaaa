#include <stdio.h>
#include <omp.h>

long fib(int n) {
    long x, y;

    if (n < 2)
        return n;

    #pragma omp task shared(x)
    x = fib(n - 1);

    #pragma omp task shared(y)
    y = fib(n - 2);

    #pragma omp taskwait
    return x + y;
}

int main() {
    int n = 20;
    long result;
    double start, end;

    start = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp single
        result = fib(n);
    }

    end = omp_get_wtime();

    printf("Fibonacci(%d) = %ld\n", n, result);
    printf("Execution Time = %f\n", end - start);

    return 0;
}
