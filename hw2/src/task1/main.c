/**
 * main.c
 *
 * Main program for task 1.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "timer.h"
#include "matrix.h"
#include "utilities.h"

#include "multiply.h"

typedef void (*f_multiply)(double *, double *, int, double*);

/**
 * Switch on order string to select multiply function.
 */
f_multiply switch_multiply(char *order)
{
    if (strcmp(order, "ijk") == 0) {
        return multiply_ijk;
    } else if (strcmp(order, "ikj") == 0) {
        return multiply_ikj;
    } else if (strcmp(order, "kij") == 0) {
        return multiply_kij;
    } else if (strcmp(order, "jik") == 0) {
        return multiply_jik;
    } else if (strcmp(order, "jki") == 0) {
        return multiply_jki;
    } else if (strcmp(order, "kji") == 0) {
        return multiply_kji;
    } else if (strcmp(order, "acc") == 0) {
        return multiply_acc;
    } else {
        printf("Error: invalid order string '%s'.\n", order);
        exit(1);
    }
}

int main(int argc, char *argv[])
{
    int i;

    // Error Checking -------------------------------------------------------
    if (argc < 2) {
        printf("Usage:\n");
        printf("    task1 n [order] [replications]\n");
        exit(1);
    }

    int n = atoi(argv[1]);
    check_positive(n, "n");

    char* order = "ijk";
    if (argc >= 3) order = argv[2];
    f_multiply multiply = switch_multiply(order);

    int replications = 1;
    if (argc >= 4) {
        replications = atoi(argv[3]);
        check_positive(replications, "replications");
    }

    // Initialization -------------------------------------------------------
    double *A = matrix(n);
    double *B = matrix(n);
    initializeAB(A, B, n);

    double* C = matrix(n);

    // Compute flops and check timer resolution.
    // Must be double or long long to prevent overflow.
    double flops = 2.0 * (double) n * (double) n * (double) n;

    long long ticks = readTSC();
    ticks = readTSC() - ticks;
    
    // Trials ---------------------------------------------------------------
    printf("[\n");
    print_header(ticks, flops);

    for (i = 0; i < replications; i++) {
        matrix_fill(C, n, 0.0);

        ticks = readTSC();
        multiply(A, B, n, C);
        ticks = readTSC() - ticks;

        print_trial(n, order, ticks, flops);
        printf("\n");
    }

    printf("]\n");

    // Clean Up -------------------------------------------------------------
    free(A);
    free(B);
    free(C);

    return 0;
}

