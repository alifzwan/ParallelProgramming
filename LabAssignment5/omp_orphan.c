/******************************************************************************
* FILE: omp_orphan.c
* DESCRIPTION:
*   OpenMP Example - Parallel region with an orphaned directive - C/C++ Version
*   This example demonstrates a dot product  being performed by an orphaned
*   loop reduction construct.  Scoping of the reduction variable is critical.
* AUTHOR: Blaise Barney  5/99
* LAST REVISED: 06/30/05
******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define VECLEN 100 // Define vector length

float a[VECLEN], b[VECLEN], sum; // Declare variables

float dotprod () { // Define function to perform dot product of two vectors a and b
  int i, tid; // Declare variables

  tid = omp_get_thread_num(); // Get thread number

  #pragma omp for reduction(+:sum) // Start parallel region with reduction to sum
    for (i = 0; i < VECLEN; i++) { // Loop through array of length VECLEN
      sum = sum + (a[i] * b[i]); // Sum the product of a and b arrays
      printf("tid = %d, i = %d\n", tid, i); // Print thread number and i
    }
}


int main (int argc, char *argv[]) {
  int i; // Declare variable

  for (i = 0; i < VECLEN; i++) { // Loop through array of length VECLEN
    a[i] = b[i] = 1.0 * i; // Initialize a and b arrays
  } 
  sum = 0.0; // Initialize sum

  #pragma omp parallel // Start parallel region
  {
    dotprod(); // Perform dot product
  }

  printf("Sum = %f\n",sum); // Print the sum
}
