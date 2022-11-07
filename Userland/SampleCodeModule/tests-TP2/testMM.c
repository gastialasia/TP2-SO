// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <testMM.h>
#include <stdlib.h>
#include <testUtil.h>
#include <programs.h>

#define MAX_BLOCKS 128

static void *myMemset(void *destination, int c, int len)
{
  uint8_t value = (uint8_t)c;
  char *origin = (char *)destination;
  while (len--)
  {
    origin[len] = value;
  }
  return destination;
}

int testMM(int argc, char argv[6][21])
{

  mm_rq mm_rqs[MAX_BLOCKS];
  uint8_t rq;
  uint32_t total;
  uint64_t max_memory;

  if (argc != 2)
  {
    printf("Only one argument expected\n");
    exit();
  }

  if ((max_memory = atoi(argv[1])) <= 0)
  {
    printf("Invalid argument: please enter a valid integer\n");
    exit();
  }

  // max_memory=0.7*134217728;

  while (1)
  {
    rq = 0;
    total = 0;

    memStatusProgram();
    sleep(2000);

    // Request as many blocks as we can
    while (rq < MAX_BLOCKS && total < max_memory)
    {
      mm_rqs[rq].size = GetUniform(max_memory - total - 1) + 1;
      mm_rqs[rq].address = malloc(mm_rqs[rq].size);

      if (mm_rqs[rq].address)
      {
        total += mm_rqs[rq].size;
      }
      rq++;
    }

    // Set
    uint32_t i;
    for (i = 0; i < rq; i++)
      if (mm_rqs[i].address)
        myMemset(mm_rqs[i].address, i, mm_rqs[i].size);

    memStatusProgram();
    sleep(2000);

    // Check
    for (i = 0; i < rq; i++)
      if (mm_rqs[i].address)
        if (!memcheck(mm_rqs[i].address, i, mm_rqs[i].size))
        {
          printf("testMM ERROR\n");
          exit();
        }

    // Free
    for (i = 0; i < rq; i++)
      if (mm_rqs[i].address)
        free(mm_rqs[i].address);
  }

  exit();
  return 0;
}