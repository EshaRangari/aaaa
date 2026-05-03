#include <stdio.h> 
#include <omp.h> 
#define N 1000000 
int main() 
{ 
long int i, n = 10000000; 
double step, x, sum=0.0, pi; 
step = 1.0/n;
#pragma omp parallel for private(x) reduction(+:sum) 
for(i = 0; i <n; i++){ 
x = (i + 0.5)* step; 
sum += 4.0 / (1.0 + x * x); 
} 
pi = step * sum; 
printf("Value of pi = %f\n",pi); 
return 0; 
} 