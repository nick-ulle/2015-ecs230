
#ifndef _matrix_h
#define _matrix_h

typedef struct {
    double *value;
    int nrow;
    int ncol;
} Matrix;

Matrix *matrix_new(int nrow, int ncol);
void matrix_free(Matrix *mat);

void matrix_fill(Matrix *mat, double value);
void matrix_copy(Matrix *src, Matrix *dest);
void matrix_triangle(Matrix *mat, char uplo);

// BLAS routines
void matrix_dgemm(
    double alpha
    , Matrix *A, char transA
    , Matrix *B, char transB,
    double beta
    , Matrix *C
);
void matrix_dgemv(
    double alpha
    , Matrix *A, char transA
    , Matrix *x
    , double beta
    , Matrix *y
);
int matrix_dpotrf(Matrix *A , char uplo);
void matrix_dtrsm(Matrix *A, char transA, double alpha, Matrix *B, char uplo);

// Pure routines
int matrix_equal(Matrix *A, Matrix *B);
void matrix_print(Matrix *mat, int precision);

#endif
