
/**
 * Retrieve Intel x86 cycle count.
 */
long long readTSC()
{
 /* read the time stamp counter on Intel x86 chips */
  union { long long complete; unsigned int part[2]; } ticks;
  __asm__ ("rdtsc; mov %%eax,%0;mov %%edx,%1"
            : "=mr" (ticks.part[0]),
              "=mr" (ticks.part[1])
            : /* no inputs */
            : "eax", "edx");
  return ticks.complete;
}

