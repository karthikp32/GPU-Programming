#include <iostream>
#include <cuda_runtime.h>
// The assignment is to implement a distributed matrix multiplication
// using a tiled method. That is, suppose you have two 1024 by 1024 matrix
// and you need to multiply them together,
// you need to split them each of them up into multiple tiles (say 4 by 4),
// and “combine/distribute” it such a way to do your matrix in parallel.

class MatrixMultiplication
{
public:
    // To do matrix multiplication, the number of columns in matrix A must
    // match the number of rows in matrix B,
    // Given a matrix A of size 2 x 3 and a matrix B of size 3 x 4,
    // the resulting matrix C will be of size 2 x 4.
    // To calculate first element of C at C[0][0], multiply first row of A with first column of B
    // To calculate second element of C at C[0][1], multiply first row of A with second column of B
    // etc.
    // Example: Let's multiply two matrices A and B

    // A = [
    //   1  2  3
    //   4  5  6
    // ]

    // B = [
    //   7   8
    //   9  10
    //   11 12
    // ]

    // Step-by-Step Process:

    // Result Matrix (C):
    // Since A is 2×3 and B is 3×2, the result matrix C will be 2×2.

    // Dot Product:
    // Each element C[i][j] is computed as the dot product of the i-th row of A and the j-th column of B.

    // First Element C[1][1]:
    // Multiply the first row of A by the first column of B:
    // C[1][1] = (1×7) + (2×9) + (3×11) = 7 + 18 + 33 = 58

    // Second Element C[1][2]:
    // Multiply the first row of A by the second column of B:
    // C[1][2] = (1×8) + (2×10) + (3×12) = 8 + 20 + 36 = 64

    // Third Element C[2][1]:
    // Multiply the second row of A by the first column of B:
    // C[2][1] = (4×7) + (5×9) + (6×11) = 28 + 45 + 66 = 139

    // Fourth Element C[2][2]:
    // Multiply the second row of A by the second column of B:
    // C[2][2] = (4×8) + (5×10) + (6×12) = 32 + 50 + 72 = 154

    // Resulting Matrix C:
    // C = [
    //   58   64
    //   139 154
    // ]

    // RTX 4090 Specs (Ada Lovelace Architecture):
    // Number of CUDA Cores: 16,384
    // Number of SMs: 128
    // Threads per Warp: 32
    // Maximum Threads per SM: 2,048
    // Maximum Warps per SM: 64 (64 warps × 32 threads/warp)
    // Max Threads=Threads per SM×Number of SMs
    // Max Threads in RTX 4090 = 2,048 × 128 = 262,144
    // Advertised TFLOPs of my rented RTX 4090 on Vast = 35.3

    // Number of data elements between two matrices = 1024 + 1024 = 2048
    // Number of dot products between row column pairs = 1024 * 1024 = 1048576
    // Number of multiplication operations = 1024 * 1024 * 1024 = 1,073,741,824
    // Number of addition operations = 1024×1024×1023=1,072,693,248
    // Number of multiplication and addition operations with one row-column pair
    // or one element of result matrix C = 2047
    // Number of result matrix elements/row-column pairs you could compute at the same time
    // = 262144 / 2047 = ~128

    // Maximum threads per block with RTX 4090: 1024 threads per block (according to ChatGPT)
    // Maximum number of blocks per RTX 4090: 256 blocks

    // Algorithm:
    // Could divide up the matrices into 256 x 256 tiles, which would be 4 tiles

    __global__ void matrix_multiply(int a[1024][1024], int b[1024][1024], int result[1024][1024])
    {
    }
};

void fillMatrix(int matrix[1024][1024])
{
    for (int i = 0; i < 1024; i++)
    {
        for (int j = 0; j < 1024; j++)
        {
            matrix[i][j] = rand() % 100; // Random values between 0-99
        }
    }
}

int main()
{
    MatrixMultiplication mat;
    int matA[1024][1024];
    int matB[1024][1024];
    int result[1024][1024];

    fillMatrix(matA);
    fillMatrix(matB);

    // Launch the kernel
    mat.matrix_multiply<<<dim3(32, 32), dim3(32, 32)>>>(matA, matB, result);
    cudaDeviceSynchronize();

    return 0;
};
