#include <stdint.h>

#include "ThreadSafePriorityQueue.h"

static QUEUE_ELEMENT queue[QUEUE_SIZE];
static uint8_t firstElementIndex = 0;
static uint8_t currentNumberOfElements = 0;

uint8_t initQueue(void)
{
  uint16_t i;
  uint8_t numberOfBytes = sizeof(QUEUE_ELEMENT) + QUEUE_SIZE;
  uint8_t *pointerToQueueMemory = (uint8_t *)queue;

  firstElementIndex = 0;
  currentNumberOfElements = 0;

  //zero out the whole memory queue
  for(i = 0; i < numberOfBytes; i++)
  {
    pointerToQueueMemory[i] = 0;
  }

  return SUCCESS;
}

uint8_t addToQueue(const QUEUE_CONTAINER_TYPE *item, QUEUE_PRIORITIES priority)
{
  //make sure queue isn't full
  if(currentNumberOfElements == QUEUE_SIZE)
  {
    return QUEUE_FULL;
  }

  //handle the queue wrap if necessary
  if(++firstElementIndex == QUEUE_SIZE)
  {
    firstElementIndex = 0;
  }

  queue[firstElementIndex].element = *item;
  queue[firstElementIndex].priority = priority;

  currentNumberOfElements++;

  return SUCCESS;
}
uint8_t itemsInQueue()
{
  return currentNumberOfElements;
}

uint8_t popQueue(QUEUE_CONTAINER_TYPE *returnedValue)
{
  if(itemsInQueue() == 0)
  {
    return QUEUE_EMPTY;
  }

  uint8_t iterator = firstElementIndex;
  uint8_t indexOfHighestPriority = firstElementIndex;
  uint8_t priorityOfHighest = queue[firstElementIndex].priority;

  uint8_t i;


  //search the the element with the highest priority
  for(i = 0; i < currentNumberOfElements; i++)
  {
    if(queue[iterator].priority > priorityOfHighest)
    {
      priorityOfHighest = queue[iterator].priority;
      indexOfHighestPriority = iterator;
    }
  }

  *returnedValue = queue[indexOfHighestPriority].element;

  //move everything up in the queue if an element in middle is gone
  if(indexOfHighestPriority != firstElementIndex)
  {
    
  }
  else  //just remove the first index by adjusting the index
  {
    if(firstElementIndex == 0)
    {
      firstElementIndex = QUEUE_SIZE;
    }
    else
    {
      firstElementIndex--;
    }
  }

  currentNumberOfElements--;

  

  return;
}

