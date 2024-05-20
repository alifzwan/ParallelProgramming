#include <stdio.h>
#include <string.h>
#include "mpi.h"

// Refer to the greetings.c code, use MPI_Bcast instead of MPI_Send and Recv.

int main(int argc, char* argv[]) {
    int         my_rank, p, source, dest, tag = 0; // rank, number of processors, source, destination, tag 
    char        message[100];  // storage for message  

    MPI_Status status;        // return status for receive
    MPI_Init(&argc, &argv);   // start up MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); // find out process rank     
    MPI_Comm_size(MPI_COMM_WORLD, &p);       // find out number of processes

    if (my_rank != 0) { // if the rank of the current processor is not 0
        sprintf(message, "Greetings from process %d!", my_rank); // print the rank of the current processor
    } 

    MPI_Bcast(message, strlen(message)+1, MPI_CHAR, 0, MPI_COMM_WORLD); // broadcast the message to all processors

    if (my_rank == 0) { // if the rank of the current processor is 0
        printf("Greetings from process 0: %s\n", message); // print the message
    } 
     
    MPI_Finalize();
} 
