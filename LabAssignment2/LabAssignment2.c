#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define ARRAY_SIZE 100000 // Size of the array to be generated

// TASK
// - Create a program that have T[100000] array size and initialize the array with random numbers. 
// - Find the smallest number from the array. 
// - Use Data Partitioning technique to distribute the load and reduce the execution time. 
// - Gather all smallest numbers from other processors to get the final smallest numbers. 
// - Analyse and explain your time reduction results for processor 1, 2, 4 and 8.


// Initializes an array with random numbers
void initialize_array(int *array, int size) {
    for (int i = 0; i < size; i++) { // Iterate over the array
        array[i] = rand(); // Generate a random number
    }
}

// Finds the smallest number in an array
int find_local_minimum(int *array, int size) {
    int local_min = INT_MAX; // Initialize the local minimum to the maximum integer value
    for (int i = 0; i < size; i++) { // Iterate over the array
        if (array[i] < local_min) { // If the current element is smaller than the local minimum
            local_min = array[i]; // Update the local minimum
        }
    }
    return local_min; // Return the local minimum
}

int main(int argc, char* argv[]) {
    int rank, size; // Rank and size of the MPI communicator
    int *T = NULL; // Array to be distributed
    int local_min, global_min; // Local and global minimum
    int *local_array; // Local array
    int local_size; // Size of the local array
    double start_time, end_time; // Start and end time of the execution

    MPI_Init(&argc, &argv); // Initialize MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get the rank of the process
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Get the size of the communicator

    srand(time(NULL) + rank); // Seed the random number generator with the current time and rank

    local_size = ARRAY_SIZE / size; // Calculate the size of the local array
    local_array = (int*)malloc(local_size * sizeof(int)); // Allocate memory for the local array

    if (rank == 0) { // Root process
        // Root process initializes the array
        T = (int*)malloc(ARRAY_SIZE * sizeof(int)); // Allocate memory for the array
        initialize_array(T, ARRAY_SIZE); // Initialize the array
    }

    start_time = MPI_Wtime();
   
    MPI_Scatter(T, local_size, MPI_INT, local_array, local_size, MPI_INT, 0, MPI_COMM_WORLD); // Scatter the array

   
    local_min = find_local_minimum(local_array, local_size); // Find the local minimum

    // Gather all local minima to the root process
    if (rank == 0) { 
        int *local_mins = (int*)malloc(size * sizeof(int)); // Allocate memory for the local minima

        MPI_Gather(&local_min, 1, MPI_INT, local_mins, 1, MPI_INT, 0, MPI_COMM_WORLD); // Gather the local minima

        global_min = find_local_minimum(local_mins, size); // Find the global minimum
        printf("The smallest number in the array is %d\n", global_min); // Print the global minimum
        free(local_mins); // Free the memory allocated for the local minima
        
    }else {
        MPI_Gather(&local_min, 1, MPI_INT, NULL, 0, MPI_INT, 0, MPI_COMM_WORLD); // Gather the local minima
    }

    end_time = MPI_Wtime(); // Get the end time of the execution

    if (rank == 0) {
        printf("Execution time with %d processors: %f seconds\n", size, end_time - start_time); // Print the execution time
    }

    // Clean up
    if (rank == 0) {
        free(T); // Free the memory allocated for the array
    }
    free(local_array); // Free the memory allocated for the local array

    MPI_Finalize();
    return 0;
}
