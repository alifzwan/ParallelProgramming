/******************************************************************************
* FILE: omp_workshare2.c
* DESCRIPTION:
*   OpenMP Example - Sections Work-sharing - C Version
*   In this example, the OpenMP SECTION directive is used to assign
*   different array operations to each thread that executes a SECTION. 
* AUTHOR: Blaise Barney  5/99
* LAST REVISED: 07/16/07
******************************************************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N 50

int main (int argc, char *argv[]) {
  int i, nthreads, tid;
  float a[N], b[N], c[N], d[N], e[N], f[N];
  double start_time, end_time;


  for (i = 0; i < N; i++) {
    a[i] = i * 1.5;
    b[i] = i + 22.35;
    c[i] = d[i] = e[i] = f[i] = 0.0;
  }
  
  for(int node = 2; node <= 16; node *= 2){
    omp_set_num_threads(node);
    start_time = omp_get_wtime(); // Start timing
    #pragma omp parallel shared(a, b, c, d, nthreads) private(i, tid)
    {

        if (node == 0){
          printf("Number of threads = %d\n", node);
        }

        printf("Thread %d starting...\n", node);

      #pragma omp sections nowait
      {
        #pragma omp section
        {
            printf("Thread %d doing section 1\n",node);
            for (i = 0; i < N; i++) {
              c[i] = a[i] + b[i];
              printf("Thread %d: c[%d]= %f\n", node, i, c[i]);
            }
        }

        #pragma omp section
        {
          printf("Thread %d doing section 2\n",node);
          for (i = 0; i < N; i++) {
            d[i] = a[i] * b[i];
            printf("Thread %d: d[%d]= %f\n", node, i, d[i]);
          }
        }
        #pragma omp section
        {
          printf("Thread %d doing section 3\n", node);
          for (i = 0; i < N; i++) {
            e[i] = a[i] - b[i];
            printf("Thread %d: e[%d]= %f\n", node, i, e[i]);
         }
        }

        #pragma omp section
        {
          printf("Thread %d doing section 4\n", node);
          for (i = 0; i < N; i++) {
            f[i] = a[i] / (b[i] + 1.0);  // Adding 1.0 to avoid division by zero
            printf("Thread %d: f[%d]= %f\n", node, i, f[i]);
          }
        }

      } 
        printf("Thread %d done.\n",node); 
    } 
    end_time = omp_get_wtime(); // End timing
    printf("Execution time with %d threads: %f seconds\n", node, end_time - start_time); 
  }

}
