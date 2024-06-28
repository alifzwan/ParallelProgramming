#include <stdio.h>
#include <mpi.h>

// Task 1:

// • Processor 0 will calculate the equation of a = (b+c)/d, b=4; c=4; d=2. 
// • Then using MPI_Bcast, broadcast the value of a to processors 1, 2, 3, 4 and 5. 

/*Output
    I am node 0 and  a is #value

    Before bcast
    I am Node 1 and  a is  #value

    After bcast
    I am Node 1 and  a is  #value
*/

int main(int argc, char* argv[]) {
    int node, size; // initialize node and size
    double a; // initialize a
    int b = 4, c = 4, d = 2; // initialize b, c, d

    MPI_Init(&argc, &argv); // initialize MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &node); // get the rank of the node
    MPI_Comm_size(MPI_COMM_WORLD, &size); // get the size of the node

    // if the node is 0
    if(node == 0) { 
        a = (double)(b + c) / d; // calculate the value of a
        printf("I am node 0 and a is %f\n", a); // print the value of a
    }

    // if the node is not 0
    if(node != 0) {
        printf("Before Bcast, I am node %d and a is %f\n", node, a); // print the value of a before Bcast
    }

    MPI_Bcast(&a, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD); // broadcast the value of a to all nodes 

    // if the node is not 0
    if(node != 0) {
        printf("After  Bcast, I am node %d and a is %f\n", node, a); // print the value of a after Bcast
    }

    MPI_Finalize();
}

