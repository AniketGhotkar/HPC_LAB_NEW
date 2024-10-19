#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv); 

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int msg1 = 100, msg2 = 200;


    if (rank == 0) {
        msg1 = 100; 
        MPI_Send(&msg1, 1, MPI_INT, 1, 0, MPI_COMM_WORLD); 

        printf("Process 0: Sent message to Process 1 and waiting for message from Process 1...\n");
        
        MPI_Recv(&msg2, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    } else if (rank == 1) {
        msg2 = 200; // Some message
        MPI_Send(&msg2, 1, MPI_INT, 0, 0, MPI_COMM_WORLD); 
        
        printf("Process 1: Sent message to Process 0 and waiting for message from Process 0...\n");

        MPI_Recv(&msg1, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    MPI_Finalize();
    return 0;
}


