#ifndef _test_mm_
#define _test_mm_

#include <stdint.h>

typedef struct MM_rq{
  void *address;
  uint32_t size;
}mm_rq;

int test_mm(int argc, char argv[6][21]);

#endif
