#include <stdio.h>
#include <string.h>
#include "mpi.h"

// Task 3

// • Refer to the greetings.c code, use MPI_Bcast instead of MPI_Send and MPI_Recv.

// MPI_Bcast - This function broadcasts a message from the process with
//             rank root to all other processes in the communicator.
//           - In other words, it sends same data from the root process to all other processes.


int main(int argc, char* argv[]) {
    int node, size;  // rank of process and number of processes 
    char message[100];  // storage for message 
    
    MPI_Init(&argc, &argv);                     // Start up MPI 
    MPI_Comm_rank(MPI_COMM_WORLD, &node);    // Find out process rank 
    MPI_Comm_size(MPI_COMM_WORLD, &size);          // Find out number of processes 
    
    if (node == 0) {
       
        strcpy(message, "Greetings from process 0!");  // Root process prepares the message to broadcast
    } 

    // Broadcast the message from root (process 0) to all other processes
    MPI_Bcast(message, 100, MPI_CHAR, 0, MPI_COMM_WORLD); // Root process broadcasts message to all processes

    // All processes print the message received from the root process
    if (node != 0) {
        printf("Process %d received: %s\n", node, message);
    }


    MPI_Finalize();    // Shut down MPI 
}
