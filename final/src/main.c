
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "matrix.h"
#include "matrix_blas.h"
#include "error.h"

/**
 * Read a link matrix input file.
 *
 * @param filename filename of input file
 * @param mat_ptr[out] resulting link matrix
 */
void read_link_matrix(char *filename, Matrix **mat_ptr)
{
    FILE *file = fopen(filename, "r");
    if (!file)
        die("Invalid data file");

    // Read number of nodes.
    int n_nodes;
    fscanf(file, "%i", &n_nodes);

    Matrix *mat = matrix_new(n_nodes, n_nodes);

    int n_idx, idx;
    for (int i = 0; i < n_nodes; i++) {
        // Read number of indexes in row.
        fscanf(file, "%i", &n_idx);

        if ((n_idx < 0) || (n_nodes < n_idx))
            die("Invalid number of indexes specified.");

        // Read each index.
        for (int j = 0; j < n_idx; j++) {
            fscanf(file, "%i", &idx);

            // Assume 1-indexing.
            if ((idx < 1) || (n_nodes < idx))
                die("Invalid index specified.");
            idx--;

            mat->value[idx + n_nodes * i] = 1.0 / n_idx;
        }
    }

    fclose(file);

    *mat_ptr = mat;
}

/**
 * Compute A + sI.
 *
 * @param mat[out] matrix A to shift
 * @param shift value s to shift by
 */
void matrix_shift(Matrix *mat, double shift)
{
    Matrix *id = matrix_new(mat->nrow, mat->ncol);
    matrix_diag(id, 1.0);

    matrix_daxpy(shift, id, mat);
}

/**
 * Use power iteration to compute the dominant eigenvector.
 *
 * @param A matrix to compute eigenvector for
 * @param[out] x initial guess on input, eigenvector on output
 * @param max_iter maximum number of iterations
 */
int power_iteration(Matrix *A, Matrix *x, int max_iter) {
    // Normalize initial guess x.
    matrix_dscal(1.0 / matrix_dnrm2(x), x);

    // Set up storage for previous guess.
    int x_nrow = x->nrow;
    Matrix *x_old = matrix_new(x_nrow, 1);
    
    int n_iter = 0;
    bool converged = false;
    while (!converged && n_iter < max_iter) {
        // Store old x and compute new x = Ax.
        matrix_copy(x, x_old);
        matrix_dgemv(1.0, A, 'n', x_old, 0.0, x);
        
        // Normalize x.
        matrix_dscal(1.0 / matrix_dnrm2(x), x);

        n_iter++;

        // Check for convergence:
        // |x - x_old| < 1.0e-6
        matrix_daxpy(-1.0, x, x_old);

        converged = true;
        for (int i = 0; i < x_nrow; i++) {
            if (fabs(x_old->value[i]) >= 1.0e-6) {
                converged = false;
                break;
            }
        }
    }

    matrix_free(x_old);

    return n_iter;
}

/**
 * Convert a string of space-separated doubles into a matrix.
 */
void parse_initial_guess(char *x_str, Matrix *x)
{
    char *end = x_str;

    for (int i = 0; i < x->nrow; i++) {
        // Make sure we're not out of values.
        if (*end == '\0')
            die("Not enough values specified to fill vector.");

        // Try reading a value for x.
        x->value[i] = strtod(x_str, &end); 

        // Check that a value was found.
        if (end == x_str)
            die("Not enough values specified to fill vector.");

        x_str = end;
    }
}

/**
 * Run the power iteration program, printing various results.
 *
 * @param[out] A matrix to compute eigenvector on input, shifted on output
 * @param[out] x initial guess on input, eigenvector on output
 * @param shift value to shift A by
 * @param max_iter maximum number of iterations
 */
void run_power_iteration(Matrix *A, Matrix *x, double shift, int max_iter)
{
    // Print the inputs.
    puts("A ="); matrix_print(A, 4); puts("");
    puts("x_0 ="); matrix_print(x, 4); puts("");

    // Run the power iteration.
    matrix_shift(A, shift);
    int n_iter = power_iteration(A, x, max_iter);

    // Print the results.
    char *msg;
    if (n_iter == max_iter)
        msg = "Power iteration (shift %.2f)"
            " failed to converge after %i iterations.\n\n";
    else
        msg = "Power iteration (shift %.2f)"
            " converged after %i iterations.\n\n";

    printf(msg, shift, n_iter);

    puts("x ="); matrix_print(x, 4); puts("");
}

int main(int argc, char **argv)
{
    // Parse the arguments.
    if (argc < 2) {
        puts(
            "Usage:\n"
            "  power LINK_MATRIX [INITIAL_GUESS] [SHIFT] [MAX_ITER]\n"
            "\n"
            "Arguments:\n"
            "  LINK_MATRIX"
            "\tlink matrix input file\n"
            "  INITIAL_GUESS"
            "\tquoted initial guess, with whitespace-separated elements\n"
            "  SHIFT"
            "\t\tshift s in A + sI\n"
            "  MAX_ITER"
            "\tmaximum number of iterations\n"
            "\n"
            "Example:\n"
            "  power chain.txt \"1.0 2.0 3.0 4.0\" 1.5 150\n"
        );
        die("At least 1 argument required.");
    }

    // Read link matrix.
    Matrix *mat;
    read_link_matrix(argv[1], &mat);

    // Read initial guess.
    Matrix *x = matrix_new(mat->ncol, 1);
    matrix_fill(x, 1.0);
    if (argc > 2) 
        parse_initial_guess(argv[2], x);

    // Read shift.
    double shift = 0.0;
    if (argc > 3) 
        shift = strtod(argv[3], NULL);

    // Read max iterations.
    int max_iter = 100;
    if (argc > 4)
        max_iter = atoi(argv[4]);
    
    run_power_iteration(mat, x, shift, max_iter);

    // Clean up.
    matrix_free(x);
    matrix_free(mat);

    return EXIT_SUCCESS;
}
