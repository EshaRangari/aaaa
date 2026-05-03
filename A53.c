#include <stdio.h>
#include <omp.h>

#define N 4

int main()
{
    int A[N][N], vector[N], result[N];
    int i,j;

    printf("Enter matrix elements:\n");
    for(i=0;i<N;i++)
        for(j=0;j<N;j++)
            scanf("%d",&A[i][j]);

    printf("Enter vector elements:\n");
    for(i=0;i<N;i++)
        scanf("%d",&vector[i]);

    double start, end;

    start = omp_get_wtime();

    #pragma omp parallel for private(j)
    for(i=0;i<N;i++)
    {
        result[i] = 0;

        for(j=0;j<N;j++)
        {
            result[i] += A[i][j] * vector[j];
        }
    }

    end = omp_get_wtime();

    printf("\nResult Vector:\n");
    for(i=0;i<N;i++)
        printf("%d ", result[i]);

    printf("\n\nStart Time : %f\n", start);
    printf("End Time   : %f\n", end);
    printf("Execution Time : %f\n", end-start);

    return 0;
}
