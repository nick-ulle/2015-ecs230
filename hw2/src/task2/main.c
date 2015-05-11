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
#include "utilities.h"

/**
 * BLAS DGEMM function.
 */
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
    double *A = matrix(n);
    double *B = matrix(n);
    initializeAB(A, B, n);

    double *C = matrix(n);

    // Compute flops and check timer resolution.
    // Must be double or long long to prevent overflow.
    double flops = 2.0 * (double) n * (double) n * (double) n;

    long long ticks = readTSC();
    ticks = readTSC() - ticks;

    // Set up for DGEMM.
    char trans = 'n';
    double alpha = 1.0;
    double beta = 0.0;

    // Trials ---------------------------------------------------------------
    printf("[\n");
    print_header(ticks, flops);

    for (i = 0; i < replications; i++) {
        matrix_fill(C, n, 0.0);

        ticks = readTSC();
        dgemm_(&trans, &trans, &n, &n, &n, &alpha, A, &n, B, &n, &beta, C, &n);
        ticks = readTSC() - ticks;

        print_trial(n, "dgemm", ticks, flops);
        printf("\n");
    }

    printf("]\n");
    
    // Clean Up -------------------------------------------------------------
    free(A);
    free(B);
    free(C);

    return 0;
}

