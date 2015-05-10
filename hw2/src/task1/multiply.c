/**
 * multiply.c
 *
 * Square matrix multiplication routines.
 */

// c_ij = a_i1 * b_1j + a_i2 * b_2j + ... + a_in * b_nj

/**
 * Multiply two square matrices.
 *
 * @param A first matrix
 * @param B second matrix
 * @param n dimension of matrices
 * @param[out] C product AB
 */
void multiply_ijk(double *A, double *B, int n, double *C)
{
    int i, j, k;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            for (k = 0; k < n; k++)
                C[i + j * n] += A[i + k * n] * B[k + j * n];
}

/**
 * Multiply two square matrices.
 */
void multiply_ikj(double *A, double *B, int n, double *C)
{
    int i, j, k;
    for (i = 0; i < n; i++)
        for (k = 0; k < n; k++)
            for (j = 0; j < n; j++)
                C[i + j * n] += A[i + k * n] * B[k + j * n];
}

/**
 * Multiply two square matrices.
 */
void multiply_jik(double *A, double *B, int n, double *C)
{
    int i, j, k;
    for (j = 0; j < n; j++)
        for (i = 0; i < n; i++)
            for (k = 0; k < n; k++)
                C[i + j * n] += A[i + k * n] * B[k + j * n];
}

/**
 * Multiply two square matrices.
 */
void multiply_jki(double *A, double *B, int n, double *C)
{
    int i, j, k;
    for (j = 0; j < n; j++)
        for (k = 0; k < n; k++)
            for (i = 0; i < n; i++)
                C[i + j * n] += A[i + k * n] * B[k + j * n];
}

/**
 * Multiply two square matrices.
 */
void multiply_kij(double *A, double *B, int n, double *C)
{
    int i, j, k;
    for (k = 0; k < n; k++)
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                C[i + j * n] += A[i + k * n] * B[k + j * n];
}

/**
 * Multiply two square matrices.
 */
void multiply_kji(double *A, double *B, int n, double *C)
{
    int i, j, k;
    for (k = 0; k < n; k++)
        for (j = 0; j < n; j++)
            for (i = 0; i < n; i++)
                C[i + j * n] += A[i + k * n] * B[k + j * n];
}

/**
 * Multiply two square matrices in ijk order using an accumulator.
 *
 * @param A first matrix
 * @param B second matrix
 * @param n dimension of matrices
 * @param[out] C product AB
 */
void multiply_acc(double *A, double *B, int n, double *C)
{
    int i, j, k;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            double sum = 0.0;
            for (k = 0; k < n; k++)
                sum += A[i + k * n] * B[k + j * n];
            C[i + j * n] = sum;
        }
}

