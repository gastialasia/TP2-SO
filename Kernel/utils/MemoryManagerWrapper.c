#include <MemoryManagerWrapper.h>
#include <MemoryManagmentADT.h>
#include <tools.h>

static MemoryManagmentADT mm;

void initMemManager(void *const restrict memoryForMemoryManager, void *const restrict managedMemory)
{
  mm = createMemoryManagment(memoryForMemoryManager, managedMemory);
}

void *alloc(unsigned int memToAlloc)
{
  return memAlloc(mm, memToAlloc);
}

void free(void *memToFree)
{
  return freeMem(mm, memToFree);
}

void memStatus(unsigned int *status)
{
  status[0] = heapSize();
  status[1] = heapLeft(mm);
  status[2] = usedHeap(mm);
}
