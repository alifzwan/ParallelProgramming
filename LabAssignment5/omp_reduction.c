/******************************************************************************
* FILE: omp_reduction.c
* DESCRIPTION:
*   OpenMP Example - Combined Parallel Loop Reduction - C/C++ Version
*   This example demonstrates a sum reduction within a combined parallel loop
*   construct.  Notice that default data element scoping is assumed - there
*   are no clauses specifying shared or private variables.  OpenMP will 
*   automatically make loop index variables private within team threads and
*   global variables shared.
* AUTHOR: Blaise Barney  5/99
* LAST REVISED: 04/06/05
******************************************************************************/


#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

// omp_reduction.c
// - This program shows how to perform a reduction operation in a parallel loop. 
// - The sum of the products of two arrays is calculated.

int main (int argc, char *argv[]) {
    int i, n=100; // i: loop index, n: number of iterations
    float a[100], b[100], sum; // a, b: arrays of size 100, sum: sum of the products of a[i] and b[i]

    for (i = 0; i < n; i++) { // loop through the array
        a[i] = b[i] = i * 1.0; // initialize a[i] and b[i] to i*1.0
    }
    sum = 0.0;

    double start_time = omp_get_wtime();

    // Parallel region
    
    // shared: a, b, n, sum
    // #pragma omp parallel for reduction(+:sum) 
    #pragma omp parallel for schedule(dynamic) reduction(+:sum)

    for (i = 0; i < n; i++) {
        sum = sum + (a[i] * b[i]);
    }
    double end_time = omp_get_wtime();

    printf("Sum = %f\n", sum);
    printf("Execution Time: %f seconds\n", end_time - start_time);
    return 0;
}
