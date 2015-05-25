
#include <stdlib.h>
#include <stdio.h>

#include "matrix.h"
#include "error.h"

// Read number of observations from first line, then read observations.

void read_data(char *filename, Matrix **x_ptr, Matrix **y_ptr)
{
    FILE *file = fopen(filename, "r");
    if (!file)
        die("Invalid data file");

    // Read number of rows.
    int nrow;
    fscanf(file, "%d", &nrow);

    Matrix *x = matrix_new(nrow, 1);
    Matrix *y = matrix_new(nrow, 1);

    // Read each (x, y) from each row.
    for (int i = 0; i < nrow; i++)
        fscanf(file, "%lf %lf", &(x->value[i]), &(y->value[i]));

    fclose(file);

    *x_ptr = x;
    *y_ptr = y;
}

void model_matrix(Matrix *x, int degree, Matrix **X_ptr)
{
    int nrow = x->nrow;

    *X_ptr = matrix_new(nrow, degree);
    double *X = (*X_ptr)->value;

    for (int i = 0; i < nrow; i++)
        X[i] = 1;

    for (int j = 1; j < degree; j++)
        for (int i = 0; i < nrow; i++) 
            X[i + j * nrow] = X[i + (j - 1) * nrow] * x->value[i];
}

int main(int argc, char **argv)
{
    // Check for arguments.
    if (argc != 3) {
        puts("Usage:\n  poly DEGREE DATA");
        die("Exactly 2 arguments required.");
    }

    int d = atoi(argv[1]);
    if (d < 1)
        die("Degree must be positive.");

    char *filename = argv[2];

    // Read the data.
    Matrix *x; Matrix *y;
    read_data(filename, &x, &y);

    //puts("x:"); matrix_print(x, 4); puts("");
    //puts("y:"); matrix_print(y, 4); puts("");

    // Compute model matrix X.
    Matrix *X;
    model_matrix(x, d, &X);

    puts("X ="); matrix_print(X, 4); puts("");

    matrix_free(x);

    // Compute A = X'X and X'y.
    Matrix *A = matrix_new(X->ncol, X->ncol);
    matrix_dgemm(1, X, 'T', X, 'N', 0, A);

    puts("A = X'X ="); matrix_print(A, 4); puts("");

    Matrix *u = matrix_new(X->ncol, y->ncol);
    matrix_dgemv(1, X, 'T', y, 0, u);

    puts("X'y ="); matrix_print(u, 4); puts("");

    matrix_free(X);

    // Compute Cholesky decomposition LL' = A.
    matrix_dpotrf(A, 'L');
    matrix_triangle(A, 'L');

    puts("L ="); matrix_print(A, 4); puts("");

    // Solve LL'b = u as Lv = u, L'b = v.
    // Solve Lv = u.
    matrix_dtrsm(A, 'N', 1, u, 'L');

    // Solve L'b = v.
    matrix_dtrsm(A, 'T', 1, u, 'L');

    puts("b ="); matrix_print(u, 10); puts("");

    // Free remaining matrices.
    matrix_free(y);
    matrix_free(u);
    matrix_free(A);

    return EXIT_SUCCESS;
}
