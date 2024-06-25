#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char* argv[]) {
    int node, size, source, dest, tag = 0;       
    char message[100];  


    MPI_Status  status;        
    MPI_Init(&argc, &argv);   
    MPI_Comm_rank(MPI_COMM_WORLD, &node);      
    MPI_Comm_size(MPI_COMM_WORLD, &size);       

    if (node != 0) {
        sprintf(message, "Greetings from process %d!", node);
        dest = 0;
        MPI_Send(message, strlen(message)+1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
    } else {     
        for (source = 1; source < size; source++){
            MPI_Recv(message, 100, MPI_CHAR, source, tag, MPI_COMM_WORLD, &status);
            printf("Test %s\n", message);
        }
    }

    MPI_Finalize();
} 
