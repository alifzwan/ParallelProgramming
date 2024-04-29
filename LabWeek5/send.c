#include "mpi.h"
#include <stdio.h>

int main(argc, argv) int argc; char *argv[];  {

int numtasks, rank, dest, source, count, tag=1;
char inmsg, outmsg='x';
MPI_Status Status;

MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);


// Process:
// 1 - If the rank is 0, send a message to rank 1
// 2 - If the rank is 1, send a message to rank 0
// 3 - If the rank is 0, receive a message from rank 1
// 4 - If the rank is 1, receive a message from rank 0
// 5 - Get the number of characters received
// 6 - Print the message received

if (rank == 0) { 

  dest = 1;
  source = 1;
  MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD); // (1)
  MPI_Recv(&inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &Status); // (3)


} else if (rank == 1) { // (2)

  dest = 0;
  source = 0;
  MPI_Recv(&inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &Status); // (4)
  MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD); // (2)

}

MPI_Get_count(&Status, MPI_CHAR, &count); // (5)
printf("Task %d: Received %d char(s) from task %d with tag %d \n", rank, count, Status.MPI_SOURCE, Status.MPI_TAG); // (6)

MPI_Finalize();
}
