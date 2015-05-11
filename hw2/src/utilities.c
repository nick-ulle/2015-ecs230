/**
 * utilities.c
 *
 * Assignment-specific utility routines shared by task 1 and task 2.
 */

#include <stdlib.h>
#include <stdio.h>

#include "matrix.h"

#define TICKS_PER_SEC 2.7e9 
// 1.5e9 on satellite

/**
 * Print header as HJSON comments.
 */
void print_header(long long ticks, double flops)
{
    printf("  # All times are in seconds.\n");
    printf("  # Assuming a %.2e Hz processor.\n", TICKS_PER_SEC);
    printf("  # Matrix multiplication will require %g flops.\n", flops);
    printf("  # TSC register has estimated resolution of %lli cycles.\n"
        , ticks);
    printf("\n");
}

/**
 * Print trial output in HJSON format.
 */
void print_trial(int n, char *order, long long ticks, double flops)
{
    printf("  {\n");
    printf("    n: %i\n", n);
    printf("    order: %s\n", order);
    printf("    cycles: %lli\n", ticks);

    double time = (double) ticks / TICKS_PER_SEC;
    printf("    time: %g\n", time);
    printf("    flops_per_cycle: %g\n", flops / ticks);
    printf("    gflops_per_sec: %g\n", 1e-9 * flops / time);
    printf("  }");
}

/**
 * Check that a named int input is positive.
 */
void check_positive(int value, char *name)
{
    if (value <= 0) {
        printf("Error: %s must be a positive integer.\n", name);
        exit(1);
    }
}

/**
 * Set up the nonzero A and B matrices.
 */
void initializeAB(double *A, double *B, int n)
{
    int i;

    // A is an e matrix with negative antidiagonal sequence.
    matrix_fill(A, n, 2.718282);
    for (i = 0; i < n; i++) {
        A[i + (n - i - 1) * n] = -(1.0 + i / 100.0);
    }

    // B is a pi matrix with positive diagonal sequence.
    matrix_fill(B, n, 3.141593);
    for (i = 0; i < n; i++) {
        B[i + i * n] = 1.0 + i / 100.0;
    }
}

