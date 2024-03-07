#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 100000000

int main(int argc, char *argv[])
{
  int cpuid = -1;
  cpu_set_t set;
  volatile int a;
  unsigned int i, c = 0;

  if (argc > 1) {
    cpuid = atoi(argv[1]);
    printf("[%5d] Pinning CPU %d\n", getpid(), cpuid);

    CPU_ZERO(&set);
    CPU_SET(cpuid, &set);

    if (sched_setaffinity(0, sizeof(cpu_set_t), &set) == -1) {
      perror("Error setting CPU affinity");
      return EXIT_FAILURE;
    }
  }

  while (1) {
    for (i=0; i<N; i++) a = 1;
    printf("[%5d pinned to: %2d running on: %2d] %8d\n", getpid(), cpuid, sched_getcpu(), c++);
  }

  return EXIT_SUCCESS;
}
