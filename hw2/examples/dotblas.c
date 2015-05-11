/**
 * dotblas.c: dot product using the BLAS library
 *
 * use: module load intel
 * compile with icc -o dotblas dotblas.c -mkl=sequential
 */

#include<stdio.h>
#include<stdlib.h>

/* Use BLAS ddot function */
void ddot_(int *n, double *x, int *incx, double *y, int *incy);

int main(int argc, char** argv)
{
  int n = atoi(argv[1]);
  int i;

  double *x = (double*)malloc(n*sizeof(double));
  double *y = (double*)malloc(n*sizeof(double));

  for ( i=0; i<n; i++ )
  {
    x[i] = 1.0/(i+1);
    y[i] = 2.0/(i+2);
  }

  double sum = 0.0;
  for ( i=0; i<n; i++ )
    sum += x[i] * y[i];
  printf("loop sum: %12.8f\n",sum);

  int inc=1;
  ddot_(&n,x,&inc,y,&inc);
  printf("ddot sum: %12.8f\n",sum);

  return 0;
}
