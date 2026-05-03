#include <stdio.h>
#include <omp.h>

#define N 4

int main()
{
    int A[N][N], result[N][N];
    int i,j;
    int scalar;

    printf("Enter scalar value: ");
    scanf("%d",&scalar);

    printf("Enter matrix elements:\n");
    for(i=0;i<N;i++)
        for(j=0;j<N;j++)
            scanf("%d",&A[i][j]);

    double start, end;

    start = omp_get_wtime();

    #pragma omp parallel for private(j)
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            result[i][j] = scalar * A[i][j];
        }
    }

    end = omp_get_wtime();

    printf("\nResult Matrix:\n");
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
            printf("%d ", result[i][j]);
        printf("\n");
    }

    printf("\nStart Time : %f\n", start);
    printf("End Time   : %f\n", end);
    printf("Execution Time : %f\n", end-start);

    return 0;
}
