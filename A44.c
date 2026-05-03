#include <stdio.h>
#include <omp.h>

#define MAX 300

int main()
{
    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    int i,j,k,n;

    double start,end;

    printf("Enter matrix size: ");
    scanf("%d",&n);

    /* Initialize matrices */
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
        {
            A[i][j] = 1;
            B[i][j] = 1;
        }

    /* -------- SERIAL MATRIX MULTIPLICATION -------- */

    start = omp_get_wtime();

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            C[i][j] = 0;

            for(k=0;k<n;k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    end = omp_get_wtime();

    printf("\n===== SERIAL EXECUTION =====\n");
    printf("Start Time : %f\n",start);
    printf("End Time   : %f\n",end);
    printf("Execution Time : %f seconds\n",end-start);


    /* -------- PARALLEL STATIC SCHEDULING -------- */

    start = omp_get_wtime();

    #pragma omp parallel for private(j,k) schedule(static)
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            C[i][j] = 0;

            for(k=0;k<n;k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    end = omp_get_wtime();

    printf("\n===== PARALLEL STATIC SCHEDULING =====\n");
    printf("Start Time : %f\n",start);
    printf("End Time   : %f\n",end);
    printf("Execution Time : %f seconds\n",end-start);


    /* -------- PARALLEL DYNAMIC SCHEDULING -------- */

    start = omp_get_wtime();

    #pragma omp parallel for private(j,k) schedule(dynamic)
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            C[i][j] = 0;

            for(k=0;k<n;k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    end = omp_get_wtime();

    printf("\n===== PARALLEL DYNAMIC SCHEDULING =====\n");
    printf("Start Time : %f\n",start);
    printf("End Time   : %f\n",end);
    printf("Execution Time : %f seconds\n",end-start);

    return 0;
}
