#include <stdio.h>
#include <mpi.h>
 
int main(int argc, char **argv){
   int size, node;
   double MPI_Wtime (void);
   double t1, t2;
   int a, b, x;

   MPI_Init(&argc,&argv);
   MPI_Comm_size(MPI_COMM_WORLD, &size);
   MPI_Comm_rank(MPI_COMM_WORLD, &node);

    if(node == 0){
        a = 20000*30000;
        printf("I am node %d and  a is %d \n", node, a);
    }

    printf("Before Bcast : Node %d  and a = %d \n", node, a);

    MPI_Bcast(&a, 1, MPI_INT, 0, MPI_COMM_WORLD);

    t1 = MPI_Wtime();

    x = 1000000000/size;

    if (node < size) {
        for (int i = 0; i < x; i++){
              a; 
        }   
    }

    t2 = MPI_Wtime();

    printf("After Bcast : Node %d  a = %d MPI_Wtime =  %1.6f\n", node, a, t2 - t1);

    MPI_Finalize(); 
}

