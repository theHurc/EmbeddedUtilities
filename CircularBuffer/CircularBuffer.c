#include <stdint.h>
#include <stdio.h>

#include "CircularBuffer.h"


static uint8_t advanceIndex(uint8_t index)
{
  if(++index == MAX_ITEMS_IN_QUEUE)
  {
    index = 0;
    LOGGER("Pointer wrapped to beginning of queue.")
  }

  return index;
}

RESULT initQueue(CircularBuffer *thisBuffer)
{
  thisBuffer->itemsInQueue = EMPTY;
  thisBuffer->queueHeadIndex = 0;
  thisBuffer->queueTailIndex = 0;

  LOGGER("Queue initialized.")

  return SUCCESS;
}

RESULT addItem(CircularBuffer *thisBuffer, const ITEM_TYPE *item)
{
  if(thisBuffer->itemsInQueue == MAX_ITEMS_IN_QUEUE)
  {
    LOGGER("Adding item failed. Queue Full")
    return QUEUE_FULL;
  }

  thisBuffer->queue[thisBuffer->queueHeadIndex] = *item;
  LOGGER("Added item to queue.")

  thisBuffer->queueHeadIndex = advanceIndex(thisBuffer->queueHeadIndex);

  thisBuffer->itemsInQueue++;

  return SUCCESS;
}

RESULT popItem(CircularBuffer *thisBuffer, ITEM_TYPE *item)
{
  if(thisBuffer->itemsInQueue == EMPTY)
  {
    LOGGER("Popping item failed. Queue empty.")
    return QUEUE_EMPTY;
  }

  *item = thisBuffer->queue[thisBuffer->queueTailIndex];
  LOGGER("Popped item from queue.")

  thisBuffer->queueTailIndex = advanceIndex(thisBuffer->queueTailIndex);

  thisBuffer->itemsInQueue--;

  return SUCCESS;
}

uint8_t getQueueSize(CircularBuffer *thisBuffer)
{
  return thisBuffer->itemsInQueue;
}

