
#include "timer.h"
#include "multiply.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TICKS_PER_SEC 2.7e9 
// 1.5e9

typedef void (*f_multiply)(double *, double *, int, double*);

/**
 * Print output in HJSON format.
 */
void print_hjson(int n, char *order, long long ticks, double flops)
{
    printf("  {\n");
    printf("    n: %i\n", n);
    printf("    order: %s\n", order);
    printf("    cycles: %lli\n", ticks);

    double time = ticks / TICKS_PER_SEC;
    printf("    time: %f\n", time);
    printf("    flops_per_cycle: %f\n", flops / ticks);
    printf("    gflops_per_sec: %f\n", 1e-9 * flops / time);
    printf("  }");
}

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

/**
 * Check a named int input is positive.
 */
void check_positive(int value, char *name) {
    if (value <= 0) {
        printf("Error: %s must be a positive integer.\n", name);
        exit(1);
    }
}

int main(int argc, char *argv[])
{
    // Error Checking -------------------------------------------------------
    if (argc < 2) {
        printf("Usage:\n");
        printf("    mult n [order] [replications]\n");
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
    // A is an e matrix with negative integer antidiagonal.
    double *A = matrix(n);
    fill(A, n, 2.718282);
    int i;
    for (i = 0; i < n; i++) {
        A[i + (n - i - 1) * n] = (double) -i;
    }

    // B is a pi matrix with integer diagonal.
    double *B = matrix(n);
    fill(B, n, 3.141593);
    for (i = 0; i < n; i++) {
        B[i + i * n] = (double) i;
    }

    double* C = matrix(n);

    // Compute flops and check timer resolution.
    int flops = 2 * n * n * n;

    long long ticks = readTSC();
    ticks = readTSC() - ticks;
    
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
        multiply(A, B, n, C);
        ticks = readTSC() - ticks;

        print_hjson(n, order, ticks, flops);
        printf("\n");
    }

    printf("]\n");

    // Clean Up -------------------------------------------------------------
    free(A);
    free(B);
    free(C);
}

