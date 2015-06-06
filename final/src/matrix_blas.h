
#ifndef _matrix_blas_h
#define _matrix_blas_h

// BLAS Level 1
void matrix_dscal(double alpha, Matrix *x);
void matrix_daxpy(double alpha, Matrix *x, Matrix *y);
double matrix_dnrm2(Matrix *x);
int matrix_idamax(Matrix *x);

// BLAS Level 2
void matrix_dgemv(
    double alpha
    , Matrix *A, char transA
    , Matrix *x
    , double beta
    , Matrix *y
);

// BLAS Level 3
void matrix_dgemm(
    double alpha
    , Matrix *A, char transA
    , Matrix *B, char transB,
    double beta
    , Matrix *C
);
void matrix_dtrsm(Matrix *A, char transA, double alpha, Matrix *B, char uplo);

#endif
