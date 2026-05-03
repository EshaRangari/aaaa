#include <stdio.h>
#include <omp.h>

#define N 10

int main()
{
    int arr[N], prefix[N];
    int i;

    printf("Enter array elements:\n");
    for(i=0;i<N;i++)
        scanf("%d",&arr[i]);

    double start, end;

    start = omp_get_wtime();

    prefix[0] = arr[0];

    for(i=1;i<N;i++)
    {
        prefix[i] = prefix[i-1] + arr[i];
    }

    end = omp_get_wtime();

    printf("\nPrefix Sum:\n");
    for(i=0;i<N;i++)
        printf("%d ", prefix[i]);

    printf("\n\nStart Time : %f\n", start);
    printf("End Time   : %f\n", end);
    printf("Execution Time : %f\n", end-start);

    return 0;
}
