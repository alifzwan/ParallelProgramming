#include <stdio.h>
#include <mpi.h>

// Task 1
// • Refer to the load.c code, add MPI_Reduce to sum all values from all processors to rank 0.

int main(int argc, char* argv[]) {
    int node, size;
    double MPI_Wtime(void);
    double t1, t2;
    int a, b, x, sum;


    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &node);

    a = 0;
    b = 1;

    t1 = MPI_Wtime();
    x = 100000/size;

    if(node < size ){
        for(int i = 0; i < x; i++) {
            a = a + b;
        }
    }

    t2 = MPI_Wtime();

    MPI_Reduce(&a, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(node == 0) {
        printf("The sum of a of all processor: %d\n", sum);
    } else {
        printf("Node %d a = %d MPI_Wtime = %1.6f\n", node, a, t2 - t1);
    }

    MPI_Finalize();

}