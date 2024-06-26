#include <stdio.h> // import the standard input/output library
#include <mpi.h> // import the MPI library


/* 
MPI_Reduce  - This function applies a reduction operation(sum, max, min, etc.) 
              to all data from all processes and stores the result in root process.

            - For example, if each process has number and the operation is sum,
              MPI_Reduce will calculate the sum of all numbers and store it in the root process.
*/              

// Task 1
// • Refer to the load.c code, add MPI_Reduce to sum all values from all processors to rank 0.


int main(int argc, char **argv){

    // size - total number of processors
    // node - the rank of current processor
    // i - loop variable
    // x - number of iterations per processor

    int size, node; // declare the variables size, node, i, x
    double MPI_Wtime (void); // declare the function MPI_Wtime
    double t1, t2; // declare the variables t1, t2
    int a, b, sum; // declare the variables a, b, sum

    MPI_Init(&argc,&argv); // initialize the MPI environment
    MPI_Comm_size(MPI_COMM_WORLD, &size); // get the total number of processors
    MPI_Comm_rank(MPI_COMM_WORLD, &node); // get the rank of the current processor

    a = 0; 
    b = 1;
    t1 = MPI_Wtime(); // get the current time
    int x = 100000/size;  // divide the number of iterations by the number of processors,  
//  x = 12500

    if (node < size) { // if the rank of the current processor is less than the total number of processors
        for (int i = 0; i < x; i++) {  // iterate through the number of iterations
            a = a + b; // add the value of b to a
        }
    }

    t2 = MPI_Wtime(); // get the current time

    // Perform the reduction to sum all 'a' values at rank 0
    MPI_Reduce(&a, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD); // reduce the value of a to the sum of all processors

   
    if(node == 0) { // if the rank of the current processor is 0
      printf("The sum 'a' from all proessors: %d\n", sum); // print the sum of all processors
    } else {
      // print the rank of the current processor, the value of a, and the time taken to execute the program
      printf("Node %d  a = %d MPI_Wtime =  %1.6f\n", node, a, t2 - t1); 
    }


    MPI_Finalize();
}