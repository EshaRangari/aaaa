#include <stdio.h> 
int main(){ 
int cores = 4; 
float clock = 3.0; 
int flops_cycle = 2; 
float flops = cores * clock * flops_cycle; 
printf("Theoretical FLOPS = %.2f GFLOPS\n",flops); 
return 0; 
}