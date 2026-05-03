#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 5

int buffer[SIZE];
int count = 0;

int main() {

    #pragma omp parallel sections shared(buffer, count)
    {
        // Producer Section
        #pragma omp section
        {
            for(int i = 1; i <= 10; i++) {

                while(count == SIZE);  // Wait if buffer full

                #pragma omp critical
                {
                    buffer[count] = i;
                    count++;
                    printf("Produced: %d\n", i);
                }
            }
        }

        // Consumer Section
        #pragma omp section
        {
            for(int i = 1; i <= 10; i++) {

                while(count == 0);  // Wait if buffer empty

                #pragma omp critical
                {
                    int item = buffer[count-1];
                    count--;
                    printf("Consumed: %d\n", item);
                }
            }
        }
    }

    return 0;
}
