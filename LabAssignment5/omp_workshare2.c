/******************************************************************************
* FILE: omp_workshare2.c
* DESCRIPTION:
*   OpenMP Example - Sections Work-sharing - C Version
*   In this example the OpenMP SECTION directive is used to assign
*   different array operations to each thread that executes a SECTION. 
* AUTHOR: Blaise Barney  5/99
* LAST REVISED: 07/16/07
******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N 50 // number of iterations in the loop

// omp_workshare2.c
// - This program demonstrates work-sharing using sections. 
// - Different sections of code are executed by different threads.

int main (int argc, char *argv[]) {
    int i, nthreads, tid; // i: loop index, nthreads: number of threads, tid: thread id
    float a[N], b[N], c[N], d[N]; // a, b, c, d: arrays of size N=50

   
    for (i = 0; i < N; i++) {
        a[i] = i * 1.5;    // initialize a[i] to i*1.5
        b[i] = i + 22.35;  // initialize b[i] to i+22.35
        c[i] = d[i] = 0.0; // initialize c[i] and d[i] to 0.0
    }

    int num_threads[] = {2, 4, 8, 16};
    char *omp_proc_bind[] = {"true", "false"};
    

    for (int k = 0; k< 2; k++){
        for (int t = 0; t < 4; t++) {
            printf("Setting OMP_PROC_BIND to %s\n", omp_proc_bind[k]);
            if(k == 0) {
                omp_set_proc_bind(omp_proc_bind_true);
            } else {
                omp_set_proc_bind(omp_proc_bind_false);
            }

            omp_set_num_threads(num_threads[t]);
            printf("Using %d threads\n", num_threads[t]);

            double start_time = omp_get_wtime();


            // Parallel Region
            // shared: a, b, c, d, nthreads
            // private: i, tid
            #pragma omp parallel shared(a, b, c, d, nthreads) private(i, tid)
            {
                tid = omp_get_thread_num(); // get the thread id

                if(tid == 0) { // if the thread id is 0
                    nthreads = omp_get_num_threads(); // get the number of threads
                    printf("Number of threads = %d\n", nthreads); // print the number of threads
                }

                printf("Thread %d starting...\n", tid); // print the thread id

                #pragma omp sections nowait // start the sections work-sharing construct
                {
                    #pragma omp section // start the first section
                    {
                        printf("Thread %d doing section 1\n", tid);

                        for(i = 0; i < N; i++) {
                            c[i] = a[i] + b[i]; // add a[i] and b[i] and store the result in c[i]
                            printf("Thread %d: c[%d]= %f\n", tid, i, c[i]); // print the value of c[i]
                        }
                    }

                    #pragma omp section
                    {
                        printf("Thread %d doing section 2\n", tid);
                        for(i = 0; i < N; i++) {
                            d[i] = a[i] * b[i];
                            printf("Thread %d: d[%d]= %f\n", tid, i, d[i]);
                        }
                    }

                    // Additional sections
                    #pragma omp section
                    {
                        printf("Thread %d doing section 3\n", tid);
                        for(i = 0; i < N; i++){
                            d[i] = a[i] - b[i];
                            printf("Thread %d: d[%d]= %f\n", tid, i, d[i]);
                        }
                    }
                    
                    #pragma omp section
                    {
                        printf("Thread %d doing section 4\n", tid);
                        for(i = 0; i < N; i++) {
                            c[i] = a[i] / (b[i] + 1); // Avoid division by zero
                            printf("Thread %d: c[%d]= %f\n", tid, i, c[i]);
                        }
                    }

                }

                #pragma omp barrier // ensure all threads have completed before proceeding
                printf("Thread %d done.\n", tid); 
            }  
                double end_time = omp_get_wtime();
                printf("Execution Time: %f seconds\n", end_time - start_time);
        } 
    }
    return 0;
}
