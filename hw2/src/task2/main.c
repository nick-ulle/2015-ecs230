/**
 * main.c
 *
 * Main program for task 2.
 *
 * Link with: 
 *      module load intel
 *      icc -o task2 main.o ... -mkl=sequential
 */

#include<stdio.h>
#include<stdlib.h>

#include "timer.h"
#include "matrix.h"

#define TICKS_PER_SEC 2.7e9 

// Use BLAS DGEMM function.
void dgemm_(
    char *transa, char *transb
    , int *m, int *n, int *k
    , double *alpha
    // ld parameters denote stride.
    , double *A, int *lda
    , double *B, int *ldb
    , double *beta
    , double *C, int *ldc
);

/**
 * Print output in HJSON format.
 */
void print_hjson(int n, char *order, long long ticks, double flops)
{
    printf("  {\n");
    printf("    n: %i\n", n);
    printf("    order: %s\n", order);
    printf("    cycles: %lli\n", ticks);

    double time = (double) ticks / TICKS_PER_SEC;
    printf("    time: %f\n", time);
    printf("    flops_per_cycle: %f\n", flops / ticks);
    printf("    gflops_per_sec: %f\n", 1e-9 * flops / time);
    printf("  }");
}

/**
 * Check a named int input is positive.
 */
void check_positive(int value, char *name) {
    if (value <= 0) {
        printf("Error: %s must be a positive integer.\n", name);
        exit(1);
    }
}

int main(int argc, char** argv)
{
    int i;

    // Error Checking -------------------------------------------------------
    if (argc < 2) {
        printf("Usage:\n");
        printf("    task2 n [replications]\n");
        exit(1);
    }

    int n = atoi(argv[1]);
    check_positive(n, "n");

    int replications = 1;
    if (argc >= 3) {
        replications = atoi(argv[2]);
        check_positive(replications, "replications");
    }

    // Initialization -------------------------------------------------------
    // A is an e matrix with negative integer antidiagonal.
    double *A = matrix(n);
    fill(A, n, 2.718282);
    for (i = 0; i < n; i++) {
        A[i + (n - i - 1) * n] = -(1.0 + i / 100.0);
    }

    // B is a pi matrix with positive diagonal sequence.
    double *B = matrix(n);
    fill(B, n, 3.141593);
    for (i = 0; i < n; i++) {
        B[i + i * n] = 1.0 + i / 100.0;
    }

    double *C = matrix(n);

    // Compute flops and check timer resolution.
    int flops = 2 * n * n * n;

    long long ticks = readTSC();
    ticks = readTSC() - ticks;

    // Set up for DGEMM.
    char trans = 'n';
    double alpha = 1.0;
    double beta = 0.0;

    // Trials ---------------------------------------------------------------
    printf("[\n");
    printf("  # All times are in seconds.\n");
    printf("  # Assuming a %.2e Hz processor.\n", TICKS_PER_SEC);
    printf("  # Matrix multiplication will require %i flops.\n", flops);
    printf("  # TSC register has estimated resolution of %lli cycles.\n"
        , ticks);
    printf("\n");

    for (i = 0; i < replications; i++) {
        fill(C, n, 0.0);

        ticks = readTSC();
        dgemm_(&trans, &trans, &n, &n, &n, &alpha, A, &n, B, &n, &beta, C, &n);
        ticks = readTSC() - ticks;

        print_hjson(n, "dgemm", ticks, flops);
        printf("\n");
    }

    printf("]\n");
    
    // Clean Up -------------------------------------------------------------
    free(A);
    free(B);
    free(C);
}

