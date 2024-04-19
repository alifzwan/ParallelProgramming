#include <stdio.h>
#include <string.h>
#include "mpi.h"

// Refer to the greetings.c code:-
// •	Write the code.
// •	Successfully compiled your code.
// •	Understand the output

int main(int argc, char* argv[]){

    int         my_rank, p, source, dest, tag=0;                                                 
    char        message[100];   

    MPI_Status  status;       // return status for  receive     
    MPI_Init(&argc, &argv);   // Start up MPI 
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);      // Find out process rank  
    MPI_Comm_size(MPI_COMM_WORLD, &p);           // Find out number of processes 

    //! Process:
    //* 1. Check if rank of current process is not 0
    //* 2. If yes it'll create a message "Greetings from process %d!" 
    //* 3. then set the rank receiver (dest) to 0  
    //* 4. and send the message to the rank receiver which is rank 0
    //* 5. if rank of current process is 0, it'll loop through all the processes
    //* 6. and receive the message from the sender

    if (my_rank != 0) { //* (1)

        sprintf(message, "Greetings from process %d!", my_rank);  //* (2)
        dest = 0; //* (3)
        MPI_Send(message, strlen(message)+1, MPI_CHAR, dest, tag, MPI_COMM_WORLD); //* (4)

    } else {      
        //* (5)
        for (source = 1; source < p; source++){ 
            MPI_Recv(message, 100, MPI_CHAR, source, tag, MPI_COMM_WORLD, &status); //* (6)
            printf("Test %s\n", message);
        }

    }
    MPI_Finalize();
} 
