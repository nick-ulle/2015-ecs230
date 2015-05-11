
#ifndef _matrix_h
#define _matrix_h

double *matrix(int n);
void matrix_fill(double *mat, int n, double value);

int matrix_equal(double *A, double *B, int n);
void matrix_print(double *mat, int n);

#endif
