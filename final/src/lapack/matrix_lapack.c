/**
 * matrix_lapack.c
 *
 * Wrappers for LAPACK routines.
 */

#include "matrix.h"

void dpotrf_(
    char *uplo
    , int *n
    , double *A, int *lda
    , int *info
);

/**
 * Compute Cholesky decomposition A = LL'.
 *
 * @param A matrix
 * @param uplo upper 'U' or lower 'L' triangular decomposition
 *
 * @return status code (= 0 success; > 0 not positive definite)
 */
int matrix_dpotrf(Matrix *A, char uplo)
{
    int info;

    dpotrf_(
        &uplo
        , &(A->ncol)
        , A->value, &(A->nrow),
        &info
    );

    return info;
}

