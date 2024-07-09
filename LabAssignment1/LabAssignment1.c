#include <mpi.h>
#include <stdio.h>

// Lab Assigment 1
// Task:
// - Refer to the below pictures, develop a ping and pong OpenMPI code 
//   based on the communication pattern from the pictures. 
// - Use MPI_Send and MPI_Recv as the routines. Send a value of x=10; y=9.

int main(int argc, char* argv[]) {
    int rank, size; // rank: process id, size: number of processes
    int x = 10, y = 9; // x: sender value, y: receiver value
    MPI_Status status; // status of the MPI communication

    MPI_Init(&argc, &argv); //  Initialize the MPI environment
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get the rank of the process
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Get the number of processes

    if (size != 8) { // Must run on 8 processes
        if (rank == 0) { 
            printf("This application is meant to be run with 8 processes.\n");
        }
        MPI_Finalize();
        return 1;
    }

    //? Define the pairs of sender and receiver
    // int pairs[rows][column]
    // {0, 4}: Process 0 sends to and receives from process 4.
    // {1, 5}: Process 1 sends to and receives from process 5.
    // {2, 6}: Process 2 sends to and receives from process 6.
    // {3, 7}: Process 3 sends to and receives from process 7.

    int pairs[4][2] = {
        {0, 4}, {1, 5}, {2, 6}, {3, 7}
    };

    for (int i = 0; i < 4; ++i) { //? Loop through the pairs 
        int sender = pairs[i][0]; 
        int receiver = pairs[i][1];

        if (rank == sender) { //? If the process is the sender

            // Sender receives the value of x
            // MPI_Send(value of x, count, type of data, receiver, tag, communicator);
            MPI_Send(&x, 1, MPI_INT, receiver, 0, MPI_COMM_WORLD); // Send x to receiver
            printf("Process %d sent %d to process %d\n", rank, x, receiver);


            // Sender receives the value of x
            // MPI_Recv(value of y, count, type of data, sender, tag, communicator, status);
            MPI_Recv(&y, 1, MPI_INT, receiver, 1, MPI_COMM_WORLD, &status); // Receive y from receiver
            printf("Process %d received %d from process %d\n", rank, y, receiver);

        }
        if (rank == receiver) { //? If the process is the receiver

            // Receiver receives the value of x
            // MPI_Recv(value of x, count, type of data, sender, tag, communicator, status);
            MPI_Recv(&x, 1, MPI_INT, sender, 0, MPI_COMM_WORLD, &status);
            printf("Process %d received %d from process %d\n", rank, x, sender);


            // Receiver receives the value of y
            // MPI_Send(value of y, count, type of data, receiver, tag, communicator);
            MPI_Send(&y, 1, MPI_INT, sender, 1, MPI_COMM_WORLD);
            printf("Process %d sent %d to process %d\n", rank, y, sender);
        }
    }

    MPI_Finalize();
    return 0;
}
