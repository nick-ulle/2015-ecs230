/**
 * matrix.c
 *
 * General-purpose matrix routines.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "matrix.h"
#include "error.h"

/**
 * Allocate memory for a matrix.
 *
 * @param nrow number of rows
 * @param ncol number of columns
 * @return pointer to new matrix
 */
Matrix *matrix_new(int nrow, int ncol) 
{
    Matrix *mat = malloc(sizeof(Matrix));
    mat->value = malloc(nrow * ncol * sizeof(double));
    mat->nrow = nrow;
    mat->ncol = ncol;

    return mat;
}

/**
 * Deallocate memory for a matrix.
 *
 * @param mat matrix to deallocate
 */
void matrix_free(Matrix *mat)
{
    free(mat->value);
    free(mat);
}

/**
 * Copy a matrix.
 *
 * @param src source matrix
 * @param dest destination matrix
 */
void matrix_copy(Matrix *src, Matrix *dest)
{
    int nrow = dest->nrow;
    int ncol = dest->ncol;

    if ((nrow != src->nrow) || (ncol != src->ncol))
        die("Mismatched dimensions in matrix_copy().");

    memcpy(dest->value, src->value, nrow * ncol * sizeof(double));
}

/**
 * Convert a matrix to upper or lower triangular.
 *
 * @param mat matrix to convert
 * @param uplo upper 'U' or lower 'T' triangular
 */
void matrix_triangle(Matrix *mat, char uplo)
{
    int nrow = mat->nrow, ncol = mat->ncol;

    switch(uplo)
    {
        case 'u':
        case 'U':
            // Upper tri
            for (int j = 0; j < ncol; j++) {
                for (int i = j + 1; i < nrow; i++) {
                    mat->value[i + j * nrow] = 0;
                }
            }
            break;

        case 'l':
        case 'L':
            // Lower tri
            for (int j = 0; j < ncol; j++) {
                for (int i = 0; i < j; i++) {
                    mat->value[i + j * nrow] = 0;
                }
            }
            break;
    }
}

/**
 * Fill a matrix with a value.
 *
 * @param mat matrix to fill
 * @param value value to fill with
 */
void matrix_fill(Matrix *mat, double value)
{
    for (int j = 0; j < mat->ncol; j++) {
        for (int i = 0; i < mat->nrow; i++) {
            mat->value[i + j * mat->nrow] = value;
        }
    }
}

/**
 * Fill a diagonal matrix.
 *
 * @param mat matrix to fill
 * @param value value to fill diagonal with
 */
void matrix_diag(Matrix *mat, double value)
{
    for (int j = 0; j < mat->ncol; j++) {
        for (int i = 0; i < mat->nrow; i++) {
            if (i == j)
                mat->value[i + j * mat->nrow] = value;
            else
                mat->value[i + j * mat->nrow] = 0.0;
        }
    }
}

/**
 * Check whether two matrices are equal.
 *
 * @param A first matrix
 * @param B second matrix
 */
int matrix_equal(Matrix *A, Matrix *B)
{
    int nrow = A->nrow, ncol = A->ncol;

    if (nrow != B->nrow || ncol != B->ncol)
        return 0;

    for (int j = 0; j < ncol; j++) {
        for (int i = 0; i < nrow; i++) {
            if (A->value[i + j * nrow] != B->value[i + j * nrow])
                return 0;
        }
    }

    return 1;
}

/**
 * Print a matrix.
 *
 * @param mat matrix to print
 * @param precision number of significant digits to print
 */
void matrix_print(Matrix *mat, int precision)
{
    // Characters _.e+00 require 6 digits.
    int width = precision + 6;

    for (int i = 0; i < mat->nrow; i++) {
        for (int j = 0; j < mat->ncol; j++) {
            // Print each row indented by two spaces.
            if (j == 0) printf(" ");

            printf(
                " % *.*g"
                , width, precision
                , mat->value[i + j * mat->nrow]
            );
        }
        printf("\n");
    }
}

/**
 * Get number of rows in a matrix.
 *
 * @param mat matrix
 * @param trans normal 'N' or transposed 'T'
 *
 * @return number of rows
 */
int matrix_nrow(Matrix *mat, char trans)
{
    switch(trans) {
        case 'n':
        case 'N':
            return mat->nrow;
        case 't':
        case 'T':
        case 'c':
        case 'C':
            return mat->ncol;
    }

    die("Invalid trans parameter in matrix_nrow().");
    return -1;
}

/**
 * Get number of columns in a matrix.
 *
 * @param mat matrix
 * @param trans normal 'N' or transposed 'T'
 *
 * @return number of columns
 */
int matrix_ncol(Matrix *mat, char trans)
{
    switch(trans) {
        case 'n':
        case 'N':
            return mat->ncol;
        case 't':
        case 'T':
        case 'c':
        case 'C':
            return mat->nrow;
    }

    die("Invalid trans parameter in matrix_ncol().");
    return -1;
}

