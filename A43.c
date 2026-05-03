#include <stdio.h>
#include <omp.h>

int main()
{
    int i;
    int partial_sum = 0;
    int total_sum = 0;

    double start, end;

    start = omp_get_wtime();

    #pragma omp parallel for private(partial_sum) lastprivate(total_sum)
    for(i = 1; i <= 20; i++)
    {
        partial_sum += i;
        total_sum = partial_sum;

        printf("Thread %d adding %d, Partial Sum = %d\n",
               omp_get_thread_num(), i, partial_sum);
    }

    end = omp_get_wtime();

    printf("\nFinal Total Sum = %d\n", total_sum);

    printf("\nStart Time : %f\n", start);
    printf("End Time   : %f\n", end);
    printf("Execution Time : %f\n", end-start);

    return 0;
}
