#include "mpi.h"
#include <stdio.h>
#define SIZE 4

// MPI_Scatter - This function distributes distinct blocks of data of a buffer
//               in the root process to each process
//             - It's like distributing pieces of a pie from root process to all process

// MPI_Gather - This function collects distinct blocks of data from each process
//              to a buffer in the root process.
//            - It's like collecting pieces of a pie from all process to root process

int main(int argc, char *argv[])  {
    int numtasks, rank, sendcount, recvcount, source; // initialize variables

    // initialize 2D array with 16 floating-point numbers
    float sendbuf[SIZE][SIZE] = { // 4x4 grid
        { 1.0 , 2.0 , 3.0 , 4.0  },
        { 5.0 , 6.0 , 7.0 , 8.0  },
        { 9.0 , 10.0, 11.0, 12.0 },
        { 13.0, 14.0, 15.0, 16.0 }  
    };

    float recvbuf[SIZE]; // initialize arrays

    MPI_Init(&argc,&argv); // initialize MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // get rank of process
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks); // get number of processes

    if (numtasks == SIZE) { // if number of processes is 4

        source = 1;         // set source to 1
        sendcount = SIZE;   // set sendcount to 4
        recvcount = SIZE;   // set recvcount to 4

        // Scatter the sendbuf array to recvbuf array
        MPI_Scatter(sendbuf, sendcount, MPI_FLOAT, recvbuf, recvcount, MPI_FLOAT, source, MPI_COMM_WORLD);

        // Print the rank and results of the recvbuf array
        printf("rank = %d  Results: %f %f %f %f\n", rank, recvbuf[0], recvbuf[1], recvbuf[2], recvbuf[3]);
    } else {
        printf("Must specify %d processors. Terminating.\n", SIZE);
    }

    // If number of processes is not SIZE, print error message and attempt to gather data
    if (numtasks != SIZE) {
        source = 1;

        // Gather the recvbuf array to sendbuf array
        MPI_Gather(recvbuf, recvcount, MPI_FLOAT, sendbuf, sendcount, MPI_FLOAT, source, MPI_COMM_WORLD);

        if (rank == 1) {
            printf(
                "Gather : rank= %d Results: %f %f %f %f %f %f %f %f\n", 
                rank, sendbuf[0][0], sendbuf[1][0], sendbuf[2][0], sendbuf[3][0], sendbuf[0][1], sendbuf[1][1], sendbuf[2][1], sendbuf[3][1]
            );
        }
    }
    MPI_Finalize();
}
