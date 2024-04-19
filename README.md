<h1 align="center">   
  Distributed and Parallel Programming
</h1> 

# Message Passing Interface (MPI)

- MPI is a standardized and portable message-passing system designed to function on a wide variety of parallel computing architectures.

## Table of Contents
  - [Basic MPI Functions](#basic-mpi-functions)

## Basic MPI Functions
### MPI_Init()
```
MPI_Init(&argc, &argv);
```
- This function initializes the MPI execution environment.
- It must be called before any other MPI routines.
- It takes two arguments: the address of the argc variable from the main function, and the address of the argv variable from the main function.

### MPI_Comm_rank()
```
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
```
- This function determines the rank of the calling process in the communicator.
- It takes two arguments: the communicator and pointer:
    -  MPI_COMM_WORLD - default communicator in which all MPI processes exist when the MPI application starts.
    -  &rank - a pointer to an integer where the rank will be stored.

### MPI_Comm_size()
```
MPI_Comm_size(MPI_COMM_WORLD, &size);
```
- This function determines the number of processes in the communicator.
- It takes two arguments: the communicator and pointer
    - MPI_COMM_WORLD - default communicator in which all MPI processes exist when the MPI application starts.
    - &size - total number of processes in the communicator.
