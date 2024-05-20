#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv){
    int size, node, i, x;
    double MPI_Wtime (void);
    double t1, t2;
    int a, b;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &node);

    if(node == 0){ // if the rank of the current processor is 0
        a = 20000*30000; // set the value of a to 20000*30000
        printf("I am node %d and  a is %d \n", node, a); // print the rank of the current processor and the value of a
    }

    printf("Before Bcast : Node %d  and a = %d \n", node, a); // print the rank of the current processor and the value of a

    MPI_Bcast(&a, 1, MPI_INT, 0, MPI_COMM_WORLD); // broadcast the value of a to all processors

    t1 = MPI_Wtime(); // get the current time

    x = 1000000000/size; // divide the number of iterations by the number of processors

    if (node < size) { // if the rank of the current processor is less than the total number of processors
        for (i = 0; i < x; i++) { // iterate through the number of iterations
            a; // increment the value of a
        }   
    }
    t2 = MPI_Wtime(); // get the current time
    printf("After Bcast : Node %d  a = %d MPI_Wtime =  %1.6f\n", node, a, t2 - t1); // print the rank of the current processor, the value of a, and the time taken to execute the program

    MPI_Finalize(); 
}
