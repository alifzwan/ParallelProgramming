/******************************************************************************
* FILE: omp_workshare1.c
* DESCRIPTION:
*   OpenMP Example - Loop Work-sharing - C/C++ Version
*   In this example, the iterations of a loop are scheduled dynamically
*   across the team of threads.  A thread will perform CHUNK iterations
*   at a time before being scheduled for the next CHUNK of work.
* AUTHOR: Blaise Barney  5/99
* LAST REVISED: 04/06/05
******************************************************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define CHUNKSIZE 10
#define N 100

int main (int argc, char *argv[]) {
    int node, tid, i, chunk=CHUNKSIZE; // declare variables
    float a[N], b[N], c[N];
    double start_time, end_time;

    
    for (i = 0; i < N; i++){
        a[i] = b[i] = i * 1.0;
    }


    for(int node = 2; node <= 16; node *= 2){
        omp_set_num_threads(node); // Set number of threads
        start_time = omp_get_wtime(); // Start timing

        #pragma omp parallel shared(a, b, c, node, chunk) private(i, tid)
        {
            if (node == 0){
                printf("Number of threads = %d\n", node);
            }

            printf("Thread %d starting...\n", node);

            #pragma omp for schedule(static,chunk)
            for (int i = 0; i < N; i++) {
                c[i] = a[i] + b[i];
                
                printf("Thread %d: c[%d]= %f\n", node, i, c[i]);
            }
        } 
    end_time = omp_get_wtime(); // End timing

    printf("Execution time with %d threads: %f seconds\n", node, end_time - start_time); 
    }

}

