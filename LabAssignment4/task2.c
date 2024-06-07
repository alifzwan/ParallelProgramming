#include <stdio.h>
#include <mpi.h>

// Task 1:
// Processor 0 will calculate the equation of a = (b+c)/d, b=4; c=4; d=2. 
// Then using MPI_Bcast, broadcast the value of a to processors 1, 2, 3, 4 and 5. 

int main(int argc, char* argv[]) {
    int my_rank, size;  // rank of process and number of processes 
    int a = 0;
    int b = 4, c = 4, d = 2;
    

    MPI_Init(&argc, &argv);                   // Start up MPI 
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);  // Find out process rank 
    MPI_Comm_size(MPI_COMM_WORLD, &size);        // Find out number of processes 

    // Processor 0 calculates the value of a
    if (my_rank == 0) {  
        a = (b + c) / d;
        printf("I am node 0 and a is %d\n", a);
    } else {
        printf("Before bcast\n");
        printf("I am node %d and a is %d\n", my_rank, a);
    }

    // Broadcast the value of a from process 0 to all other processes
    MPI_Bcast(&a, 1, MPI_INT, 0, MPI_COMM_WORLD); // Broadcast the value of a to all other processors

    if (my_rank != 0) {
        printf("After bcast\n");
        printf("I am node %d and a is %d\n", my_rank, a);
    }
    MPI_Finalize(); // Shut down MPI
}
