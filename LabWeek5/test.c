#include "mpi.h"
#include <stdio.h>

int main(argc, argv) int argc; char *argv[];  {

int numtasks, rank, dest, source, count, tag=1;
char inmsg, outmsg='x';
MPI_Status Status;

MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);

// Check if there are an even number of tasks
if (numtasks % 2 != 0) {
    printf("Error: Number of tasks must be even.\n");
    MPI_Finalize();
    return 1;
}

// Determine destination and source ranks
if (rank % 2 == 0) {
    dest = rank + 1;
    source = rank + 1;
} else {
    dest = rank - 1;
    source = rank - 1;
}

// Send and receive messages
MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
MPI_Recv(&inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &Status);

// Get the number of characters received
MPI_Get_count(&Status, MPI_CHAR, &count);
printf("Task %d: Received %d char(s) from task %d with tag %d \n", rank, count, Status.MPI_SOURCE, Status.MPI_TAG);

MPI_Finalize();
}