#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char* argv[]) {
    int my_rank;        // rank of process 
    int p;              // number of processes 
    char message[100];  // storage for message 
    
    MPI_Init(&argc, &argv);                     // Start up MPI 
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);    // Find out process rank 
    MPI_Comm_size(MPI_COMM_WORLD, &p);          // Find out number of processes 
    
    if (my_rank == 0) {
        for (int source = 1; source < p; source++) {
            
            sprintf(message, "Greetings from process %d!", source); // Root process (rank 0) initializes message for broadcasting
            MPI_Bcast(message, 100, MPI_CHAR, 0, MPI_COMM_WORLD); // Root process broadcasts message to all processes
            printf("Process 0 broadcasting: %s\n", message);
        }
    } else {
        for (int i = 1; i < p; i++) {
            // Non-root processes receive the broadcasted message
            MPI_Bcast(message, 100, MPI_CHAR, 0, MPI_COMM_WORLD);
            if (my_rank == i) {
                printf("Process %d received: %s\n", my_rank, message);
            }
        }
    }

    MPI_Finalize();    /* Shut down MPI */
    return 0;
}
