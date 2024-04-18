#include <stdio.h>
#include <mpi.h>

//*    MPI:
//?  - Its a standardized and portable message-passing system 
//?    designed to function on a wide variety of parallel computing architectures.

int main(int argc, char *argv[]) {


    // numprocs - number of processes
    // rank     - rank of the calling process in the communicator
    // namelen  - length of the name
    int size, p, namelen;

    
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
