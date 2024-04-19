#include <stdio.h>
#include <string.h>
#include "mpi.h"

// Modify the code as follows:-
// •	Let rank 0 send message “Hello from Rank 0” to all other processors.
// •	Let all other processors receive from Rank 0 and print “Hello from Rank 0 and I am Rank [print the rank number]”.

int main(int argc, char* argv[]) {

    // my_rank - rank of the calling process in the communicator, 
    // p       - number of processes 
    // source  - rank of the sender,
    // dest    - rank of the receiver,
    // tag     - message tag
    
    int         my_rank, p, source, dest, tag=0;  
    char        message[100];  // storage for message  
    MPI_Status  status;        // return status for receive     

    MPI_Init(&argc, &argv);   // Start up MPI 
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);      // Get process rank  
    MPI_Comm_size(MPI_COMM_WORLD, &p);            // Get number of processes 


    //! Process:
    //* 1 - Check if the rank of current process is 0 
    //* 2 - If it does, it sets the message to "Hello from Rank 0"
    //* 3 - Then, we enter a loop where we send the message to all other ranks 
    //* 4 - Inside the loop, we send the message to the destination rank
    //* 5 - If the rank is not 0, we receive the message from rank 0
    //* 6 - We print the message received from rank 0


    if (my_rank == 0) { //* (1)
       strcpy(message, "Hello from Rank 0"); //* (2)
       for(dest = 1; dest < p; dest++) { //* (3)   
            MPI_Send(message, strlen(message)+1, MPI_CHAR, dest, tag, MPI_COMM_WORLD); //* (4)
       }
    } else {  //* (5)      
        MPI_Recv(message, 100, MPI_CHAR, 0, tag, MPI_COMM_WORLD, &status);
        printf("%s and I am Rank %d\n", message, my_rank);  //* (6)
    }
    MPI_Finalize();
} 
