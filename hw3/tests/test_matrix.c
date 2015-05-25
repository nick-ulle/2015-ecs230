
#include "matrix.h"

int main(int argc, char **argv)
{
}

int test_matmult()
{
    int m = 5, k = 5, n = 3;

    Matrix *A = matrix_new(m, k);

    Matrix *B = matrix_new(k, n);

    matrix_dgemm(1.2, A, 'n', B, 'n', 0, C);

    return matrix_equal(C, target);
}

int test_vecmult()
{
    int m = 5, k = 5, n = 1;

    Matrix *A = matrix_new(m, k);
    matrix_fill(A, -1);

    Matrix *B = matrix_new(k, n);
    // (1, 0, 0, -3.14, 0)
    matrix_fill(B, 0);
    B[0] = 1;
    B[3] = -3.14;

    matrix_dgemm(1.2, A, 'n', B, 'n', 0, C);

    matrix_destroy(A);
    return matrix_equal(C, target);
}

int test_cholesky()
{
}

