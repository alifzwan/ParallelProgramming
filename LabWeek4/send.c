#include "mpi.h"
#include <stdio.h>

// Refer to the send.c code:-
// •	Write the code.
// •	Successfully compiled your code.
// •	Understand the output

int main(argc,argv) int argc; char *argv[]; {
    
    int numtasks, rank, dest, source, rc, count, tag=1; // MPI variables
    char inmsg, outmsg='x';
    MPI_Status Stat; // MPI status variable

    MPI_Init(&argc,&argv); // Initialize the MPI environment
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks); // Get the number of processes
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get the rank of the process

    if (rank == 0){ // Rank 0 sends message to Rank 1
        dest = 1; // Destination rank
        source = 1; // Source rank
        MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD); // Send message to Rank 1
        MPI_Recv(&inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &Stat); // Receive message from Rank 1
    } else if (rank == 1) { // Rank 1 sends message to Rank 0
        dest = 0; // Destination rank
        source = 0; // Source rank
        MPI_Recv(&inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &Stat); // Receive message from Rank 0
        MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD); // Send message to Rank 0
    }

    MPI_Get_count(&Stat, MPI_CHAR, &count); // Get the number of characters received
    
    // Print the message received
    printf("Task %d: Received %d char(s) from task %d with tag %d \n", rank, count, Stat.MPI_SOURCE, Stat.MPI_TAG); 
    MPI_Finalize(); // Finalize the MPI environment
}
