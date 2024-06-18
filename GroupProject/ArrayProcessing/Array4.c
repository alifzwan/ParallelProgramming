#include <stdio.h>  // Standard I/O library
#include <omp.h>    // OpenMP library
#include <stdlib.h> // Standard library
#include <math.h>   // Math library
#define SIZE 1000   // Size of the 2D array

// GROUP PROJECT:
// • Calculate the sum of the square roots of all elements in a 2D array 

int main() {
  int num_threads;  
  float array[SIZE][SIZE]; // 2D array

  // Initialize the array with sample values
  for (int i = 0; i < SIZE; i++) {  // Iterate from 0 to 999
    for (int j = 0; j < SIZE; j++) { 
      array[i][j] = (i * SIZE) + j + 1; // Sample initialization
    }
  }

  //* The array would look like this for SIZE = 4
  // array = [
  //      [1, 2, 3, 4],     // First row (i = 0)
  //      [5, 6, 7, 8],     // Second row (i = 1)
  //      [9, 10, 11, 12],  // Third row (i = 2)
  //      [13, 14, 15, 16], // Fourth row (i = 3)
  // ]
  //
  // For SIZE = 4, the array would look like this
  // array[i][j] = i * SIZE + j + 1;
  // array[0][0] = 0 * 4 + 0 + 1 = 1


  // Loop to run the code with different number of threads (1, 2, 4, 8)
  for (num_threads = 1; num_threads <= 8; num_threads = num_threads * 2) {
    omp_set_num_threads(num_threads);    // Set the number of threads to be used for the parallel loop within the current iteration
    double sum = 0.0; // Resetting sum to 0 for each thread iteration. This ensures accurate accumulation of square root values for each thread run 
    double start_time = omp_get_wtime(); // Start time measurement

    // OpenMP parallel loop for calculating the sum of squares
    #pragma omp parallel for schedule(static) reduction(+:sum)// Static scheduling
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
          sum += sqrt(array[i][j]);
        }
    }

    //* The array would look like this for SIZE = 4
    // array = [
    //      [1, 2, 3, 4],     // First row  (i = 0)
    //      [5, 6, 7, 8],     // Second row (i = 1)
    //      [9, 10, 11, 12],  // Third row  (i = 2)
    //      [13, 14, 15, 16], // Fourth row (i = 3)
    // ]
    //
    // sum += sqrt(array[i][j]);
    // sum += sqrt(array[0][0]) = sqrt(1) = 1.0;
    // sum += sqrt(array[0][1]) = sqrt(2) ≈ 1.414
    // sum += sqrt(array[0][2]) = sqrt(3) ≈ 1.732
    // sum += sqrt(array[0][3]) = sqrt(4) = 2.0



    double end_time = omp_get_wtime(); // End time measurement
    double execution_time = end_time - start_time; // Calculate the execution time

    printf("Number of threads: %d, Sum: %f, Execution Time: %f seconds\n",
           num_threads, sum, execution_time);
  }

  return 0;
}


//! Different if using static scheduling and dynamic scheduling:

//?  Static Schedule:
// • The loop iterations are divided equally upfront among the available threads.
// • Each thread gets assigned a specific set of elements to process, and it's responsible for those elements throughout the loop.

//?  Dynamic Schedule:
// • Loop iterations are distributed on-demand during the loop execution.
// • A chunk of iterations (often a single iteration) is made available in a shared pool.
// • Threads grab iterations from the pool as they become available.

//*  Choosing the Right Schedule:
// • If the workload for each iteration is relatively uniform, 
//   schedule(static) is a good choice due to its simplicity and lower overhead.

// • If the workload for each iteration varies significantly, 
//   schedule(dynamic) might be better to achieve a more balanced workload across threads, even though it introduces some overhead.

//* In my specific code:
// • The workload for each iteration is relatively uniform (calculating the square root of a single element with a fixed computational cost),
//   so schedule(static) is a good choice for this scenario.