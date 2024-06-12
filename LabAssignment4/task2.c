#include <stdio.h>
#include <mpi.h>

// Task 1:
// Processor 0 will calculate the equation of a = (b+c)/d, b=4; c=4; d=2. 
// Then using MPI_Bcast, broadcast the value of a to processors 1, 2, 3, 4 and 5. 

int main(int argc, char* argv[]) {
    int node, size;
    double a;
    int b = 4, c = 4, d = 2;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &node);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(node == 0) {
        a = (double)(b + c) / d;
        printf("I am node 0 and a is %f\n", a);
    }

    if(node != 0) {
        printf("Before Bcast:\n");
        printf("I am node %d and a is %f\n", node, a);
    }

    MPI_Bcast(&a, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if(node != 0) {
        printf("After Bcast:\n");
        printf("I am node %d and a is %f\n", node, a);
    }

    MPI_Finalize();
}

