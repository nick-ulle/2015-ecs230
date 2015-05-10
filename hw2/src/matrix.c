/**
 * matrix.c
 *
 * General-purpose matrix routines.
 */

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
    int c, r;
    for (c = 0; c < n; c++) {
        for (r = 0; r < n; r++) {
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
    int r, c;
    for (r = 0; r < n; r++) {
        for (c = 0; c < n; c++) {
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
    int r, c;
    for (r = 0; r < n; r++) {
        for (c = 0; c < n; c++) {
            // Print each row indented by two spaces.
            if (c == 0) printf(" ");

            printf(" %f", mat[r + c * n]);
        }
        printf("\n");
    }
}

