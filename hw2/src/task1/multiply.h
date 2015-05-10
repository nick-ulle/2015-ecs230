
#ifndef _multiply_h
#define _multiply_h

void multiply_ijk(double *A, double *B, int n, double *C);
void multiply_ikj(double *A, double *B, int n, double *C);
void multiply_jik(double *A, double *B, int n, double *C);
void multiply_jki(double *A, double *B, int n, double *C);
void multiply_kij(double *A, double *B, int n, double *C);
void multiply_kji(double *A, double *B, int n, double *C);

void multiply_acc(double *A, double *B, int n, double *C);

#endif
