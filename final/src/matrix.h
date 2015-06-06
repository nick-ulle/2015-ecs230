
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
void matrix_diag(Matrix *mat, double value);
void matrix_copy(Matrix *src, Matrix *dest);
void matrix_triangle(Matrix *mat, char uplo);

// Pure routines
int matrix_equal(Matrix *A, Matrix *B);
void matrix_print(Matrix *mat, int precision);
int matrix_ncol(Matrix *mat, char trans);
int matrix_nrow(Matrix *mat, char trans);

#endif
