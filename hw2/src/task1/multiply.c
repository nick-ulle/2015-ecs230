
#include <stdlib.h>
#include <stdio.h>

/**
 * Allocate memory for a square matrix.
 *
 * @param n dimension of matrix
 */
double *matrix(int n) 
{
    return malloc(n * n * sizeof(double));
}

/**
 * Fill a square matrix with a value.
 *
 * @param mat matrix to fill
 * @param n dimension of matrix
 * @param value value to fill with
 */
void fill(double *mat, int n, double value)
{
    for (int c = 0; c < n; c++) {
        for (int r = 0; r < n; r++) {
            mat[r + c * n] = value;
        }
    }
}

/**
 * Check whether two square matrices are equal.
 *
 * @param A first matrix
 * @param B second matrix
 * @param n dimension of matrices
 */
int equal(double *A, double *B, int n)
{
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (A[r + c * n] != B[r + c * n]) return 0;
        }
    }

    return 1;
}

/**
 * Print a square matrix.
 *
 * @param mat matrix to print
 * @param n dimension of matrix
 */
void print_matrix(double *mat, int n)
{
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            // Print each row indented by two spaces.
            if (c == 0) printf(" ");

            printf(" %f", mat[r + c * n]);
        }
        printf("\n");
    }
}

// c_ij = a_i1 * b_1j + a_i2 * b_2j + ... + a_in * b_nj

/**
 * Multiply two square matrices.
 *
 * @param A first matrix
 * @param B second matrix
 * @param n dimension of matrices
 * @param[out] C product AB
 */
void multiply_ijk(double *A, double *B, int n, double *C)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                C[i + j * n] += A[i + k * n] * B[k + j * n];
}

/**
 * Multiply two square matrices.
 */
void multiply_ikj(double *A, double *B, int n, double *C)
{
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++)
            for (int j = 0; j < n; j++)
                C[i + j * n] += A[i + k * n] * B[k + j * n];
}

/**
 * Multiply two square matrices.
 */
void multiply_jik(double *A, double *B, int n, double *C)
{
    for (int j = 0; j < n; j++)
        for (int i = 0; i < n; i++)
            for (int k = 0; k < n; k++)
                C[i + j * n] += A[i + k * n] * B[k + j * n];
}

/**
 * Multiply two square matrices.
 */
void multiply_jki(double *A, double *B, int n, double *C)
{
    for (int j = 0; j < n; j++)
        for (int i = 0; i < n; i++)
            for (int k = 0; k < n; k++)
                C[i + j * n] += A[i + k * n] * B[k + j * n];
}

/**
 * Multiply two square matrices.
 */
void multiply_kij(double *A, double *B, int n, double *C)
{
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                C[i + j * n] += A[i + k * n] * B[k + j * n];
}

/**
 * Multiply two square matrices.
 */
void multiply_kji(double *A, double *B, int n, double *C)
{
    for (int k = 0; k < n; k++)
        for (int j = 0; j < n; j++)
            for (int i = 0; i < n; i++)
                C[i + j * n] += A[i + k * n] * B[k + j * n];
}

/**
 * Multiply two square matrices in ijk order using an accumulator.
 *
 * @param A first matrix
 * @param B second matrix
 * @param n dimension of matrices
 * @param[out] C product AB
 */
void multiply_acc(double *A, double *B, int n, double *C)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            double sum = 0.0;
            for (int k = 0; k < n; k++)
                sum += A[i + k * n] * B[k + j * n];
            C[i + j * n] = sum;
        }
}

