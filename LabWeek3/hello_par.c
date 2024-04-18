#include <stdio.h>
#include <mpi.h>

// Refer to the hello_par.c code, modify the code as follows:-
// •	Given variable for MPI_Comm_size is size
// •	Given variable for MPI_Comm_rank is p
// •	Given display for printf is “ Greetings from process __ and total number of processors is __. I am running on __”

// argc - number of command line arguments passed into the program
// argv[] - array of command line arguments passed into the program

int main(int argc, char *argv[]) {

    int size, p, namelen; //number of processes, rank of the calling process in the communicator, length of the name
    char processor_name[MPI_MAX_PROCESSOR_NAME];  // name of the processor

    //! Initialize the MPI execution environment
    MPI_Init(&argc, &argv); // Initialize the MPI execution environment

        MPI_Comm_size(MPI_COMM_WORLD, &size); // Get the number of processes
        
        MPI_Comm_rank(MPI_COMM_WORLD, &p); // Get the rank of the calling process in the communicator
        
        MPI_Get_processor_name(processor_name, &namelen); // Get the name of the processor

        // print the rank, processor name and number of processes
        printf("Greetings from process %d and total number of processors is %d. I am running on %s\n", p, size, processor_name); 

    
    MPI_Finalize(); // Terminate the MPI execution environment
    //! Finalize the MPI execution environment
 }
