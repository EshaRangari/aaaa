#include <stdio.h> 
#include <omp.h> 
int main(){ 
int i, n; 
double start, end; 
printf("Enter number of threads : "); 
scanf("%d",&n); 
omp_set_num_threads(n); 
printf("\nSequential Output : \n"); 
start = omp_get_wtime(); 
for(i = 0; i < n; i++) 
{ 
    printf("welcome\n"); 
} 

end = omp_get_wtime(); 
printf("Sequential Time : %f\n", end - start); 
printf("\nParallel Output : \n"); 
start = omp_get_wtime(); 
#pragma omp parallel 
{ 
    printf("welcome thread %d\n", omp_get_thread_num()); 
} 

end = omp_get_wtime();

printf("Parallel Time : %f\n", end - start); 
printf("\nParallel for Output : \n"); 
start = omp_get_wtime(); 
#pragma omp parallel for 
for(i = 0; i < n; i++) 
{ 
    printf("welcome iteration %d by thread %d\n", i, omp_get_thread_num()); 
} 

end = omp_get_wtime(); 
printf("Parallel For Time : %f\n", end - start); 
return 0; 
}