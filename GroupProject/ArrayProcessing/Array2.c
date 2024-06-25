#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <math.h> 
#define SIZE 1000

// Calculate the sum of the square roots of all elements in a 2D array 

int main() {
  int node, num_threads; 
  double sum = 0.0;
  float array[SIZE][SIZE];

  // Initialize the array (you can modify this with random values)
  for (node = 0; node < SIZE; node++) {
    for (int j = 0; j < SIZE; j++) {
      array[node][j] = node * SIZE + j + 1; // Sample initialization
    }
  }

  // Loop to run the code with different number of threads
  for (num_threads = 1; num_threads <= 8; num_threads = num_threads * 2) {
    omp_set_num_threads(num_threads); // Set the number of threads
    sum = 0.0;
    double start_time = clock(); // Start time measurement

    // OpenMP parallel loop for calculating the sum of squares
    #pragma omp parallel for private(node) reduction(+:sum)
    for (node = 0; node < SIZE * SIZE; node++) {
      sum += sqrt(array[node / SIZE][node % SIZE]);
    }

    double end_time = clock(); // End time measurement
    double execution_time = (end_time - start_time) / CLOCKS_PER_SEC;

    printf("Number of threads: %d, Sum: %f, Execution Time: %f seconds\n",
           num_threads, sum, execution_time);
  }

  return 0;
}



// Thread Increase and Execution Time:

// The increase in execution time with 8 threads deviates from the expected speedup with more threads. 

// There are a couple of reasons why this might happen:
// -  Overhead: Adding more threads introduces overhead for the operating system to manage them. Context switching between threads takes time, and if the workload is small (like in this case), the overhead can outweigh the benefit of parallelization.
// -  False Sharing: If the array elements being accessed by different threads are close together in memory, it can lead to cache invalidation. This can slow down performance as threads compete for cache lines.
// -  For small array sizes and simple calculations like this, the overhead from managing threads might negate the benefit of parallelization. With 8 threads, the context switching cost might be dominating the execution time.

// Here's what you can try to improve the results:
// - Increase Array Size: Experiment with a larger array size to see if the overhead is less significant compared to the actual calculations, allowing more threads to be utilized effectively.
// - Explore Thread Affinity: Investigate thread affinity techniques to minimize cache invalidation due to false sharing. This might involve controlling which CPU cores specific threads are assigned to.