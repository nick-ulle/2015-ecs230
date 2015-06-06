/**
 * matrix_blas.c
 *
 * Wrappers for BLAS routines.
 */

#include "matrix.h"

// Declarations --------------------------------------------------

// BLAS Level 1
void dscal_(
    int *n
    , double *alpha
    , double *x, int *incx
);

void daxpy_(
    int *n
    , double *alpha
    , double *x, int *incx
    , double *y, int *incy
);

double dnrm2_(
    int *n
    , double *x, int *incx
);

int idamax_(
    int *n
    , double *x, int *incx
);

// BLAS Level 2
void dgemv_(
    char *trans
    , int *m, int *n
    , double *alpha
    , double *A, int *lda
    , double *x, int *incx
    , double *beta
    , double *y, int *incy
);

// BLAS Level 3
void dgemm_(
    char *transa, char *transb
    , int *m, int *n, int *k
    , double *alpha
    , double *A, int *lda
    , double *B, int *ldb
    , double *beta
    , double *C, int *ldc
);

void dtrsm_(
    char *side, char *uplo
    , char *transa, char *diag
    , int *m, int *n
    , double *alpha
    , double *A, int *lda
    , double *B, int *ldb
);

// Definitions --------------------------------------------------

/**
 * Compute ax, storing the result in x.
 */
void matrix_dscal(double alpha, Matrix *x)
{
    int inc = 1;
    // Treat matrices as vectors.
    int nrow = x->nrow * x->ncol;

    dscal_(
        &nrow
        , &alpha
        , x->value, &inc
    );
}

/**
 * Compute ax + y, storing the result in y.
 */
void matrix_daxpy(double alpha, Matrix *x, Matrix *y)
{
    int inc = 1;
    // Treat matrices as vectors.
    int nrow = x->nrow * x->ncol;

    daxpy_(
        &nrow
        , &alpha
        , x->value, &inc
        , y->value, &inc
    );
}

/**
 * Compute the Euclidean norm of x.
 */
double matrix_dnrm2(Matrix *x)
{
    int inc = 1;

    return dnrm2_(&(x->nrow), x->value, &inc);
}

/**
 * Compute the index of the max absolute value entry.
 */
int matrix_idamax(Matrix *x)
{
    int inc = 1;

    return idamax_(&(x->nrow), x->value, &inc);
}

/**
 * Compute aAx + by, storing the result in y.
 */
void matrix_dgemv(
    double alpha
    , Matrix *A, char transA
    , Matrix *x
    , double beta
    , Matrix *y
)
{
    int inc = 1;

    dgemv_(
        &transA
        , &(A->nrow), &(A->ncol)
        , &alpha
        , A->value, &(A->nrow)
        , x->value, &inc
        , &beta
        , y->value, &inc
    );
}

/**
 * Solve Ax = aB for x.
 *
 * @param uplo upper 'U' or lower 'L' triangular matrix A
 */
void matrix_dtrsm(Matrix *A, char transA, double alpha, Matrix *B
    , char uplo)
{
    char side = 'L';
    char diag = 'N';

    dtrsm_(
        &side, &uplo
        , &transA, &diag
        , &(B->nrow), &(B->ncol)
        , &alpha
        , A->value, &(A->nrow)
        , B->value, &(B->nrow)
    );
}

/**
 * Compute aAB + bC, storing the result in C.
 */
void matrix_dgemm(
    double alpha
    , Matrix *A, char transA
    , Matrix *B, char transB,
    double beta
    , Matrix *C
)
{
    int m = matrix_nrow(A, transA);
    int n = matrix_ncol(B, transB);
    int k = matrix_ncol(A, transA);

    dgemm_(
        &transA, &transB
        , &m, &n, &k
        , &alpha
        , A->value, &(A->nrow)
        , B->value, &(B->nrow)
        , &beta
        , C->value, &(C->nrow)
    );
}

