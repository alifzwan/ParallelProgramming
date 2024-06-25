/******************************************************************************
* FILE: omp_workshare1.c
* DESCRIPTION:
*   OpenMP Example - Loop Work-sharing - C/C++ Version
*   In this example the iterations of a loop are scheduled dynamically
*   across the team of threads.  A thread will perform CHUNK iterations
*   at a time before being scheduled for the next CHUNK of work.
* AUTHOR: Blaise Barney  5/99
* LAST REVISED: 04/06/05
******************************************************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define CHUNKSIZE 10 // number of iterations per thread that will be executed at a time
#define N 100 // number of iterations in the loop

// omp_workshare1.c
// - This program demonstrates loop work-sharing using dynamic scheduling.
// - Each thread processes a chunk of iterations.

int main (int argc, char *argv[]) {
    // nthreads: number of threads, tid: thread id, i: loop index, chunk: number of iterations per thread
    int nthreads, tid, i, chunk; 
    float a[N], b[N], c[N]; // a, b, c: arrays of size N=100

    /* Some initializations */
    for (i = 0; i < N; i++){
        a[i] = b[i] = i * 1.0; // 
    }
    chunk = CHUNKSIZE;

    int num_threads[] = {2, 4, 8, 16};
    
    double start_time = omp_get_wtime(); // get the start time
    // parallel region
    // shared: a, b, c, nthreads, chunk
    // private: i, tid
    #pragma omp parallel shared(a, b, c, nthreads, chunk) private(i, tid) 
    {
        tid = omp_get_thread_num(); // get the thread id
        if (tid == 0) {
            nthreads = omp_get_num_threads(); // get the number of threads
            printf("Number of threads = %d\n", nthreads); // print the number of threads
        }
        printf("Thread %d starting...\n", tid);

        #pragma omp for schedule(dynamic, chunk)
        
            for (i = 0; i < N; i++) {
                c[i] = a[i] + b[i];
                printf("Thread %d: c[%d]= %f\n", tid, i, c[i]);
            }

        // ensure all threads have completed before proceeding    
        #pragma omp barrier 
    } 
    double end_time = omp_get_wtime();
    printf("Execution Time: %f seconds\n", end_time - start_time);

    return 0;
}

//! OpenMP (Open Multi-Processing) 
// - It's an application programming interface (API) that supports 
//   multi-platform shared memory multiprocessing programming in C, C++, and Fortran. 
// - It is widely used for parallel programming on multi-core processors.

//! Key Concepts in OpenMP
//*  Parallel Region ('#pragma omp parallel'):
// - A block of code that will be executed by multiple threads.
// - Declared using '#pragma omp parallel' directive.

//* Work-sharing Construct:
// - Used to divide tasks among threads.
//   For example:
//      - '#pragma omp for'     : for loop parallelism 
//      - '#pragma omp sections': form dividing into section

//* Synchronization Construct:
// - Ensure correct ordering and access to shared resources
//   For example:
//      - '#pragma omp critical', 
//      - '#pragma omp barrier', 
//      - '#pragma omp atomic',
//      - '#pragma omp master'

//* Reductions:
// - Combine values from all threads into a single result
// - Declared using 'reduction(+:sum)' to sum values across threads

//* Environment Variables:
// - Used to control the execution of OpenMp programs
//   For example:
//      - OMP_NUM_THREADS: set the number of threads to use 
//      - OMP_PROC_BIND  : set the thread affinity 

