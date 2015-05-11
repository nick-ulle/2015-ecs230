
#ifndef _utilities_h
#define _utilities_h

void print_header(long long ticks, double flops);
void print_trial(int n, char *order, long long ticks, double flops);

void check_positive(int value, char *name);

void initializeAB(double *A, double *B, int n);

#endif
