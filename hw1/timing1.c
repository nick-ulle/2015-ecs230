/*
 * timing1.c: test timing functions
 */

#include "stdio.h"
#include "time.h"
#include "sys/time.h"
#include "math.h"
#include "stdlib.h"

volatile double gtod(void)
{
  static struct timeval tv;
  static struct timezone tz;
  gettimeofday(&tv,&tz);
  return tv.tv_sec + 1.e-6*tv.tv_usec;
}

int main(int argc, char** argv)
{
  int n = atoi(argv[1]);
  clock_t clk;
  double t, t_cpu, t_real;

  clk = clock();
  t = gtod();

  /* do something */
  double sum = 0.0;
  int i;
  for ( i = 0; i < n; i++ )
    sum += sqrt((double) i);

  long long delta_clock = clock() - clk;
  t_cpu = ( (double) delta_clock ) / CLOCKS_PER_SEC;
  t_real = gtod() - t;

  printf(" clock:  %15lld  \n", delta_clock );
  printf(" t cpu:  %15.6f s\n", t_cpu );
  printf(" t real: %15.6f s\n", t_real );

}
