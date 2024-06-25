#include "mpi.h"
#include <stdio.h>
#define SIZE 4
int main(int argc, char *argv[])  {
    int size, node, sendcount, recvcount, source;

    float sendbuf[SIZE][SIZE] = {
        {1.0, 2.0, 3.0, 4.0},
        {5.0, 6.0, 7.0, 8.0},
        {9.0, 10.0, 11.0, 12.0},
        {13.0, 14.0, 15.0, 16.0}  
    };

    float recvbuf[SIZE];

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &node);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size == SIZE) {

        source = 1;

        sendcount = SIZE;

        recvcount = SIZE;

        MPI_Scatter(sendbuf,sendcount,MPI_FLOAT,recvbuf,recvcount,
                    MPI_FLOAT,source,MPI_COMM_WORLD);

        printf("rank= %d  Results: %f %f %f %f\n", node, recvbuf[0],
        recvbuf[1],recvbuf[2],recvbuf[3]);

    } else {
        printf("Must specify %d processors. Terminating.\n",SIZE);
    }

    if(size != SIZE) {

        source = 1;

        MPI_Gather(recvbuf,recvcount,MPI_INT,sendbuf,sendcount,
             MPI_INT,source,MPI_COMM_WORLD);

        if (node == 1) {
            printf(
                "Gather : rank= %d Results: %f %f %f %f %f %f %f %f\n", 
                node, 
                sendbuf[0][0], 
                sendbuf[1][0], 
                sendbuf[2][0], 
                sendbuf[3][0], 
                sendbuf[0][1], 
                sendbuf[1][1], 
                sendbuf[2][1], 
                sendbuf[3][1]
            );
        }
    }
    MPI_Finalize();
}
