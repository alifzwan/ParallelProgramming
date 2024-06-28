/******************************************************************************
* FILE: omp_reduction.c
* DESCRIPTION:
*   OpenMP Example - Combined Parallel Loop Reduction - C/C++ Version
*   This example demonstrates a sum reduction within a combined parallel loop
*   construct.  Notice that default data element scoping is assumed - there
*   are no clauses specifying shared or private variables.  OpenMP will 
*   automatically make loop index variables private within team threads, and
*   global variables shared.
* AUTHOR: Blaise Barney  5/99
* LAST REVISED: 04/06/05
******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
  int i, n = 100;             // declare variables
  float a[100], b[100], sum;  // declare variables

  // Initialize arrays
  for (i = 0; i < n; i++){
    a[i] = b[i] = i * 1.0; // Initialize a and b arrays
  }
  
  sum = 0.0;

  #pragma omp parallel for reduction(+:sum) // Start parallel region with reduction to sum
  
    for (i=0; i < n; i++){ // Loop through array
      sum = sum + (a[i] * b[i]); // Sum the product of a and b arrays
    }
  

  printf("Sum = %f\n", sum); // Print the sum
}
