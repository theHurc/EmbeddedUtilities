//Generic circular buffer
#include <stdint.h>
#include <stdio.h>

#include "CircularBuffer/CircularBuffer.h"

//! Advances the index respecting wrap around.
static uint8_t advanceIndex(uint8_t index, const uint8_t maxQueueSize)
{
  if(++index == maxQueueSize)
  {
    index = 0;
    LOGGER("Pointer wrapped to beginning of queue.")
  }

  return index;
}

void resetQueue(circularBuffer * const thisBuffer)
{
THREAD_SAFE_BEGIN

  thisBuffer->itemsInQueue = 0;
  thisBuffer->queueHeadIndex = 0;
  thisBuffer->queueTailIndex = 0;

  LOGGER("Queue reset.")

THREAD_SAFE_END

  return;
}

RESULT addItem(circularBuffer * const thisBuffer, const void *item)
{
  THREAD_SAFE_BEGIN

  RESULT result;
  uint16_t index = 0;

  uint8_t *bufferPtr;
  uint8_t *itemPtr;

  if( thisBuffer == NULL )
  {
    LOGGER("Buffer pointer NULL; Not adding item");
    result = NULL_BUFFER_PTR;
  }
  else if( item == NULL )
  {
    LOGGER("Item pointer NULL; Not adding item");
    result = NULL_ITEM_PTR;
  }
  else if(thisBuffer->itemsInQueue == thisBuffer->maxQueueSize)
  {
    LOGGER("Adding item failed. Queue Full")
    result = QUEUE_FULL;
  }
  else
  {
    bufferPtr = ((uint8_t *)thisBuffer->buffer);
    itemPtr = ((uint8_t *)item);

    bufferPtr += ((thisBuffer->queueHeadIndex) * thisBuffer->bytesPerElement);

    //Manually fill in all the buffer element byte by byte
    for( index = 0; index < thisBuffer->bytesPerElement; index++)
    {

      *bufferPtr = *itemPtr;

      bufferPtr += 1;
      itemPtr += 1;
    }

    thisBuffer->queueHeadIndex = advanceIndex(thisBuffer->queueHeadIndex, thisBuffer->maxQueueSize);

    thisBuffer->itemsInQueue++;

    LOGGER("Added item to queue.")

    result = SUCCESS;
  }

THREAD_SAFE_END

  return result;
}

RESULT popItem( circularBuffer * const thisBuffer, void *item)
{
THREAD_SAFE_BEGIN

  RESULT result;
  uint16_t index =0;

  uint8_t *bufferPtr;
  uint8_t *itemPtr;

  if( thisBuffer == NULL )
  {
    LOGGER("Buffer pointer NULL; Not adding item");
    result = NULL_BUFFER_PTR;
  }
  else if( item == NULL )
  {
    LOGGER("Item pointer NULL; Not adding item");
    result = NULL_ITEM_PTR;
  }
  else if(thisBuffer->itemsInQueue == 0)
  {
    LOGGER("Popping item failed. Queue empty.")
    result = QUEUE_EMPTY;
  }
  else
  {
    bufferPtr = ((uint8_t *)thisBuffer->buffer);
    itemPtr = ((uint8_t *)item);

    bufferPtr += ((thisBuffer->queueTailIndex) * thisBuffer->bytesPerElement);

    //Manually fill in all the buffer element byte by byte
    for( index = 0; index < thisBuffer->bytesPerElement; index++)
    {

      *itemPtr = *bufferPtr;

      bufferPtr += 1;
      itemPtr += 1;
    }

    thisBuffer->queueTailIndex = advanceIndex(thisBuffer->queueTailIndex, thisBuffer->maxQueueSize);

    thisBuffer->itemsInQueue--;

    LOGGER("Popped item from queue.")

    result = SUCCESS;
  }

THREAD_SAFE_END

  return result;
}

uint8_t getItemsInQueue(circularBuffer * const thisBuffer)
{
  uint8_t size;

THREAD_SAFE_BEGIN

  size = thisBuffer->itemsInQueue;

THREAD_SAFE_END

  return size;
}

