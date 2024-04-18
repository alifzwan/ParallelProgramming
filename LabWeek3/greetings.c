#include <stdio.h>
#include <string.h>
#include "mpi.h"
// Refer to the greetings.c code:-
// •	Write the code.
// •	Successfully compiled your code.
// •	Understand the output
int main(int argc, char* argv[]) 
{
    int         my_rank, p, source, dest, tag=0;  //rank of the calling process in the communicator, number of processes
                                                  //rank of the sender, rank of the receiver, message tag
    char        message[100];  // storage for message  

    MPI_Status  status;        // return status for  receive     
    MPI_Init(&argc, &argv);   // Start up MPI 
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);      // Find out process rank  
    MPI_Comm_size(MPI_COMM_WORLD, &p);       // Find out number of processes 
    if (my_rank != 0) {
        sprintf(message, "Greetings from process %d!", my_rank); // Create message
        dest = 0;
        MPI_Send(message, strlen(message)+1, MPI_CHAR, dest, tag, MPI_COMM_WORLD); // Use strlen+1 so that '\0' gets transmitted 
    } else {      
        for (source = 1; source < p; source++){ // my_rank == 0
            MPI_Recv(message, 100, MPI_CHAR, source, tag, MPI_COMM_WORLD, &status);
            printf("Test %s\n", message);
        }
    }
    MPI_Finalize();
} 
