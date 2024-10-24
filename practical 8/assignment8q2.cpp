#include <mpi.h>
#include <iostream>

using namespace std; 

int main(int argc, char** argv) {
    int rank, size;
    int data, recv_data;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    data = rank + 1;  

    cout << "Process " << rank << " has initial data " << data << endl;

    int right = (rank + 1) % size;   
    int left = (rank - 1 + size) % size; 

    MPI_Send(&data, 1, MPI_INT, right, 0, MPI_COMM_WORLD);
    MPI_Recv(&recv_data, 1, MPI_INT, left, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    cout << "Process " << rank << " received data " << recv_data << " from process " << left << endl;

    MPI_Finalize();
    return 0;
}


