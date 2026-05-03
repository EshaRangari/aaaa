#include <stdio.h> 
#include <omp.h> 
int main() 
{ 
int n, i; 
float scalar; 
printf("Enter size of vector: "); 
scanf("%d", &n); 
float vector[n], result[n]; 
printf("Enter vector elements:\n"); 
for (i = 0; i < n; i++) 
{ 
    scanf("%f", &vector[i]);
} 

printf("Enter scalar to add: "); 
scanf("%f", &scalar); 
double start, end; 
// ================= Sequential Addition ================= 
start = omp_get_wtime(); 
for (i = 0; i < n; i++) 
{ 
    result[i] = vector[i] + scalar; 
} 

end = omp_get_wtime();

printf("\n--- Sequential Result ---\n"); 
for (i = 0; i < n; i++) 
{ 
    printf("%.2f ", result[i]); 
} 

printf("\nSequential Time: %f seconds\n", end - start); 
// ================= Parallel Addition ================= 
start = omp_get_wtime(); 
#pragma omp parallel for 
for (i = 0; i < n; i++) 
{ 
    result[i] = vector[i] + scalar; 
} 

end = omp_get_wtime(); 
printf("\n--- Parallel Result ---\n"); 
for (i = 0; i < n; i++) 

{ 
    printf("%.2f ", result[i]); 
} 

printf("\nParallel Time: %f seconds\n", end - start); 
return 0; 
}