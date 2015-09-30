#include <stdio.h>
#include "ThreadSafePriorityQueue.h"

int main()
{
  uint32_t value = 42;
  printf("This is the main");
  initQueue();
  addToQueue(&value, HIGH);
  return 0;
}
