#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv); 

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size); 

    if (world_size < 5) {
        printf("This program requires at least 5 processes.\n");
        MPI_Abort(MPI_COMM_WORLD, 1); 
    }
    // Create a new communicator group of 5 processes
    MPI_Comm group_comm;
    MPI_Comm_split(MPI_COMM_WORLD, 0, 0, &group_comm);

    int group_size;
    MPI_Comm_size(group_comm, &group_size); // Get size of the new communicator

    int rank;
    MPI_Comm_rank(group_comm, &rank); // Get rank in the new communicator

    printf("Rank %d out of %d in the communicator group.\n", rank, group_size);

    MPI_Comm_free(&group_comm);
    MPI_Finalize(); // Finalize MPI
    return 0;
}

