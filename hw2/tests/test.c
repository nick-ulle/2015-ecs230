
#include <stdio.h>

#include "matrix.h"
#include "multiply.h"

int test_equal()
{
    double A[] = {4141, 36, 95618, 2.30, 2.42, 2.90, -1.5, -8, -0.001};
    double B[] = {4141, 36, 95618, 2.30, 2.42, 2.90, -1.5, -8, -0.001};

    return matrix_equal(A, B, 3);
}

int test_multiply()
{
    int passed = 1;

    double I[] = {1, 0, 0, 1};
    double B[] = {1, 1, 1, 1};

    double C[] = {0, 0, 0, 0};

    // IB = B
    multiply_ijk(I, B, 2, C);

    passed &= matrix_equal(B, C, 2);

    // BI = B
    matrix_fill(C, 2, 0.0);
    multiply_ijk(B, I, 2, C);

    passed &= matrix_equal(B, C, 2);

    return passed;
}

int test_multiply2()
{
    double A[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    double B[] = {1, -1, 0.5, 0, 1, -1, 0.5, 1, 1, -1, 0.5, 2, 1, -1, 0.5, 3};

    double C[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    double target[] = {
        0.5, 1, 1.5, 2
        , 13.5, 15, 16.5, 18
        , 26.5, 29, 31.5, 34
        , 39.5, 43, 46.5, 50
    };

    multiply_ijk(A, B, 4, C);

    return matrix_equal(target, C, 4);
}

int main()
{
    test_equal() ? printf(".") : printf("x");
    test_multiply() ? printf(".") : printf("x");
    test_multiply2() ? printf(".") : printf("x");

    printf("\n");

    return 0;
}
