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


    //! Process: This code demonstrates sending and receiving messages between two processes.
    //* 1 - Check if the rank of current process is 0
    //* 2 - if it does, it sets rank of receiver (dest) to 1 and rank of sender (source) to 1
    //* 3 - Then, it send message to Rank 1, simultaneously receiving message from Rank 1
    //* 4 - if the rank is not 0, it sets rank of receiver (dest) to 0 and rank of sender (source) to 0
    //* 5 - Then, it receives message from Rank 0, simultaneously sending message to Rank 0
    //* 6 - Get the count of the message received for printing the message 
    //* 7 - Print the message received from the sender

    if (rank == 0){ //* (1)

        dest = 1; //* (2) 
        source = 1; 
        MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD); //* (3)
        MPI_Recv(&inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &Stat);

    } else if (rank == 1) { //* (4)

        dest = 0; 
        source = 0; 
        MPI_Recv(&inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &Stat); //* (5)
        MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD); 

    }

    MPI_Get_count(&Stat, MPI_CHAR, &count); //* (6)
    
    
    printf("Task %d: Received %d char(s) from task %d with tag %d \n", rank, count, Stat.MPI_SOURCE, Stat.MPI_TAG); //* (7)
    MPI_Finalize(); 
}
