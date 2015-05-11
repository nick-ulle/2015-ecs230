/**
 * dotblas.c: dot product using the BLAS library
 *
 * use: module load intel
 * compile with icc -o dotblas dotblas.c -mkl=sequential
 */

#include<stdio.h>
#include<stdlib.h>

#include "timer.h"
#include "matrix.h"

// Use BLAS DGEMM function.
void dgemm_(
    char *transa, char *transb
    , int *m, int *n, int *k
    , double *alpha
    // ld parameters denote stride.
    , double *A, int *lda
    , double *B, int *ldb
    , double *beta
    , double *C, int *ldc
);

/* Use BLAS ddot function */
// void ddot_(int *n, double *x, int *incx, double *y, int *incy);

int main(int argc, char** argv)
{
    int i;
    int n = 3;

    // A is an e matrix with negative integer antidiagonal.
    double *A = matrix(n);
    fill(A, n, 2.718282);
    int i;
    for (i = 0; i < n; i++) {
        A[i + (n - i - 1) * n] = -(1.0 + i / 100);
    }
    print_matrix(A, n);
    printf("\n");

    // B is a pi matrix with positive diagonal sequence.
    double *B = matrix(n);
    fill(B, n, 3.141593);
    for (i = 0; i < n; i++) {
        B[i + i * n] = 1.0 + i / 100;
    }
    print_matrix(B, n);
    printf("\n");

    double *C = matrix(n);
    fill(C, n, 0.0);

    char trans = 'n';
    double alpha = 1.0;
    double beta = 0.0;
    dgemm_(&trans, &trans, &n, &n, &n, &alpha, A, &n, B, &n, &beta, C, &n);
    
    print_matrix(C, n);
}

