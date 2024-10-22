#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void print_vector(int *vec, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", vec[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    int rank, size;
    static const int n = 4; // Size of the matrix and vector (n x n matrix)
    
    // Static allocations
    static int matrix[4][4];  // Static matrix of size n x n
    static int vector[4];      // Static vector of size n
    static int result[4];      // Static result vector of size n

    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Only the root process initializes the matrix and vector
    if (rank == 0) {
        // Fill matrix with values (for demonstration, use sequential values)
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i][j] = i + j; // Example values
            }
        }

        // Fill vector with values
        for (int i = 0; i < n; i++) {
            vector[i] = i + 1; // Example values
        }
    }

    // Broadcast the vector to all processes
    MPI_Bcast(vector, n, MPI_INT, 0, MPI_COMM_WORLD);

    // Calculate the number of rows each process will handle
    int rows_per_process = n / size;
    
    // Allocate local matrix and result statically
    static int local_matrix[4][4];   // Adjust size if needed for larger matrices
    static int local_result[4];        // Adjust size if needed for larger matrices

    // Scatter the matrix rows to all processes
    MPI_Scatter(matrix, rows_per_process * n, MPI_INT, local_matrix, rows_per_process * n, MPI_INT, 0, MPI_COMM_WORLD);

    // Perform local matrix-vector multiplication
    for (int i = 0; i < rows_per_process; i++) {
        local_result[i] = 0;
        for (int j = 0; j < n; j++) {
            local_result[i] += local_matrix[i][j] * vector[j];
        }
    }

    // Gather results from all processes to the root process
    MPI_Gather(local_result, rows_per_process, MPI_INT, result, rows_per_process, MPI_INT, 0, MPI_COMM_WORLD);

    // Only the root process prints the result
    if (rank == 0) {
        printf("Resulting vector:\n");
        print_vector(result, n);
    }

    // Finalize MPI
    MPI_Finalize();

    return 0;
}
