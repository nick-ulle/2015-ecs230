
#include "timer.h"
#include "multiply.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define TICKS_PER_SEC 1.5e9

void print_it(char *order, long long ticks, double flops)
{
    printf("%s: {\n", order);
    printf("  cycles: %lli\n", ticks);

    double time = ticks / TICKS_PER_SEC;
    printf("  time: %f\n", time);
    printf("  flops_per_cycle: %f\n", flops / ticks);
    printf("  gflops_per_sec: %f\n", 1e-9 * flops / time);
    printf("}\n");
}

int main(int argc, char *argv[])
{
    // Error Checking -------------------------------------------------------
    if (argc != 2) {
        printf("Exactly one argument required.\n");
        exit(1);
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        printf("Argument must be a positive integer.\n");
        exit(1);
    }

    // Initialization -------------------------------------------------------

    // Allocate matrices.
    double *A = matrix(n, 0.0);
    for (int i = 0; i < n; i++) {
        A[i + i * n] = 1.0;
    }

    double *B = matrix(n, 1.5);
    for (int i = 0; i < n; i++) {
        B[i + i * n] = (double) i;
    }

    double* C = matrix(n, 0.0);

    // Compute flops and check timer resolution.
    double flops = 2 * pow((double) n, 3.0);

    long long ticks = readTSC();
    ticks = readTSC() - ticks;
    
    // Trials ---------------------------------------------------------------
    printf("# n is %i.\n", n);
    printf("# Assuming a %.2e Hz processor.\n", TICKS_PER_SEC);
    printf("# TSC register has a resolution of %lli cycles.\n", ticks);
    printf("# Matrix multiplication will require %.0f flops.\n", flops);

    printf("\n");

    // Run timings.
    ticks = readTSC();
    multiply_ijk(A, B, n, C);
    ticks = readTSC() - ticks;
    print_it("ijk", ticks, flops);

    fill(C, n, 0.0);
    ticks = readTSC();
    multiply_ikj(A, B, n, C);
    ticks = readTSC() - ticks;
    print_it("ikj", ticks, flops);

    fill(C, n, 0.0);
    ticks = readTSC();
    multiply_jik(A, B, n, C);
    ticks = readTSC() - ticks;
    print_it("jik", ticks, flops);

    fill(C, n, 0.0);
    ticks = readTSC();
    multiply_jki(A, B, n, C);
    ticks = readTSC() - ticks;
    print_it("jki", ticks, flops);

    fill(C, n, 0.0);
    ticks = readTSC();
    multiply_kij(A, B, n, C);
    ticks = readTSC() - ticks;
    print_it("kij", ticks, flops);

    fill(C, n, 0.0);
    ticks = readTSC();
    multiply_kji(A, B, n, C);
    ticks = readTSC() - ticks;
    print_it("kji", ticks, flops);

    // Clean up.
    free(A);
    free(B);
    free(C);
}

