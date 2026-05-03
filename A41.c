#include <stdio.h>
#include <omp.h>

int main()
{
    char *family[] = {"Father", "Mother", "Brother", "Sister"};
    int n = 4;

    double start, end;

    start = omp_get_wtime();

    #pragma omp parallel num_threads(n)
    {
        int id = omp_get_thread_num();
        printf("Family Member: %s executed by Thread ID: %d\n", family[id], id);
    }

    end = omp_get_wtime();

    printf("\nStart Time : %f\n", start);
    printf("End Time   : %f\n", end);
    printf("Execution Time : %f\n", end-start);

    return 0;
}
