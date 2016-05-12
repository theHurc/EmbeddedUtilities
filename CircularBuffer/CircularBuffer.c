//Generic circular buffer
//Added a cool comment
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
THREAD_SAFE_BEGIN

  thisBuffer->itemsInQueue = EMPTY;
  thisBuffer->queueHeadIndex = 0;
  thisBuffer->queueTailIndex = 0;

  LOGGER("Queue initialized.")

THREAD_SAFE_END

  return SUCCESS;
}

RESULT addItem(CircularBuffer *thisBuffer, const ITEM_TYPE *item)
{
  RESULT result = SUCCESS;

THREAD_SAFE_BEGIN

  if(thisBuffer->itemsInQueue == MAX_ITEMS_IN_QUEUE)
  {
    LOGGER("Adding item failed. Queue Full")
    result = QUEUE_FULL;
  }
  else
  {
    thisBuffer->queue[thisBuffer->queueHeadIndex] = *item;
    LOGGER("Added item to queue.")

    thisBuffer->queueHeadIndex = advanceIndex(thisBuffer->queueHeadIndex);

    thisBuffer->itemsInQueue++;

    result = SUCCESS;
  }

THREAD_SAFE_END

  return result;
}

RESULT popItem(CircularBuffer *thisBuffer, ITEM_TYPE *item)
{
  RESULT result = SUCCESS;

THREAD_SAFE_BEGIN

  if(thisBuffer->itemsInQueue == EMPTY)
  {
    LOGGER("Popping item failed. Queue empty.")
    result = QUEUE_EMPTY;
  }
  else
  {
    *item = thisBuffer->queue[thisBuffer->queueTailIndex];
    LOGGER("Popped item from queue.")

    thisBuffer->queueTailIndex = advanceIndex(thisBuffer->queueTailIndex);

    thisBuffer->itemsInQueue--;

    result = SUCCESS;
  }

THREAD_SAFE_END

  return result;
}

uint8_t getQueueSize(CircularBuffer *thisBuffer)
{
  uint8_t size;

THREAD_SAFE_BEGIN

  size = thisBuffer->itemsInQueue;

THREAD_SAFE_END

  return size;
}

