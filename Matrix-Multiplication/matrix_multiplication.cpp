#include <iostream>
#include <cuda_runtime.h>


class MatrixMultiplication {
public:
    
    __global__ void matrix_multiply((int a[1024][1024], int b[1024][1024], int result[1024][1024]) {
        
    }
};

    void fillMatrix(int matrix[1024][1024]) {
    for (int i = 0; i < 1024; i++) {
        for (int j = 0; j < 1024; j++) {
            matrix[i][j] = rand() % 100; // Random values between 0-99
        }
    }
}


int main() {
    MatrixMultiplication mat;
    int[][] matA = new int[1024][1024];
    int[][] matB = new int[1024][1024];
    int[][] result = {0};
    
    mat.fillMatrix(matA);
    mat.fillMatrix(matB);

    mat.matrix_multiply()
    return 0;
}
