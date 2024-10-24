#include <mpi.h>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
    int rank, size;
    const int n = 8; 
    vector<int> A(n);
    int local_sum = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

  
    if (rank == 0) {
        for (int i = 0; i < n; ++i) {
            A[i] = i + 1; 
        }
    }

    MPI_Bcast(A.data(), n, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        for (int i = 0; i < n / 2; ++i) {
            local_sum += A[i]; 
        }
    } else if (rank == 1) {
        for (int i = n / 2; i < n; ++i) {
            local_sum += A[i]; 
        }
    }
    
    cout << "Process " << rank << " local sum: " << local_sum << endl;
  
    int total_sum;
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        cout << "Total Sum: " << total_sum << endl;
    }

    MPI_Finalize();
    return 0;
}

