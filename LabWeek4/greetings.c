#include <stdio.h>
#include <string.h>
#include "mpi.h"

// Modify the code as follows:-
// •	Let rank 0 send message “Hello from Rank 0” to all other processors.
// •	Let all other processors receive from Rank 0 and print “Hello from Rank 0 and I am Rank [print the rank number]”.

int main(int argc, char* argv[]) 
{
    MPI_Init(NULL, NULL);   // Initialize the MPI environment

    int my_rank; // Rank of process            
    int my_size; // Number of processes

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); // Get the rank of the process  
    MPI_Comm_size(MPI_COMM_WORLD, &my_size); // Get the number of processes           

    if (my_rank == 0) { // Rank 0 sends message to all other processors
        for(int i = 1; i < my_size; i++){
            MPI_Send(NULL, 0, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    } else { // All other processors receive from Rank 0 and print
        MPI_Recv(NULL, 0, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // Receive from Rank 0
        printf("Hello from Rank 0 and I am Rank %d\n", my_rank);
    }

    
    MPI_Finalize();
} 
