#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// max allocated memory is N * BUF_SIZE
#define N 64
#define BUF_SIZE (256 * 1024 * 1024)

int main(int argc, char *argv[])
{
  struct timespec sleeper = { .tv_sec = 0, .tv_nsec = 250000000L };
  unsigned int i, c = 0, n = 0;
  volatile int v;

  char **memory = (char**)malloc(N*sizeof(char*));

  while (n < N) {
    nanosleep(&sleeper, NULL);
    if ((memory[n] = malloc(BUF_SIZE)) == NULL) break;
    n++;
    printf("[%5d] Allocated %2.4f GB of memory\n", getpid(), (float)BUF_SIZE / (1024*1024*1024) * n);
  }

  while (1) {
    int m, ofs;

    m = random() % n;
    ofs = random() % BUF_SIZE;
    memory[m][ofs] = '!';

    for (i=0; i<5000; i++) v = i;

    if (c++ % (256*1024) == 0) printf("[%5d] Performed %2.3f M random writes\n", 
                                      getpid(), (float)c / (1024*1024));
  }
  return EXIT_SUCCESS;
}
