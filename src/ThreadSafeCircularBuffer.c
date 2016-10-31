#include "ThreadSafeCircularBuffer.h"
#include "UserDefines.h"

#include <stdint.h>
#include <stdio.h>

//! Advances the index respecting wrap around.
static uint8_t advanceIndex(uint8_t current_index, const uint8_t queue_size)
{
  if(++current_index == queue_size)
  {
    current_index = 0;
    LOGGER("Pointer wrapped to beginning of queue.")
  }

  return current_index;
}

void resetQueue(CircularBuffer * const buffer)
{
THREAD_SAFE_BEGIN

  if( buffer == NULL )
  {
    LOGGER("Buffer pointer NULL; Not resetting queue");
  }
  else
  {
    buffer->_items_in_queue = 0;
    buffer->_queue_head_index = 0;
    buffer->_queue_tail_index = 0;

    LOGGER("Queue reset.")
  }

THREAD_SAFE_END

  return;
}

RESULT addItem(CircularBuffer * const buffer, const void * const item)
{
THREAD_SAFE_BEGIN

  RESULT result;
  uint16_t index = 0;

  uint8_t *bufferPtr;
  uint8_t *itemPtr;

  if( buffer == NULL )
  {
    LOGGER("Buffer pointer NULL; Not adding item");
    result = NULL_BUFFER_PTR;
  }
  else if( item == NULL )
  {
    LOGGER("Item pointer NULL; Not adding item");
    result = NULL_ITEM_PTR;
  }
  else if(buffer->_items_in_queue == buffer->_max_queue_size)
  {
    LOGGER("Adding item failed. Queue Full")
    result = QUEUE_FULL;
  }
  else
  {
    bufferPtr = ((uint8_t *)buffer->_buffer);
    itemPtr = ((uint8_t *)item);

    bufferPtr += ((buffer->_queue_head_index) * buffer->_bytes_per_element);

    //Manually fill in all the buffer element byte by byte
    for( index = 0; index < buffer->_bytes_per_element; index++)
    {

      *bufferPtr = *itemPtr;

      bufferPtr += 1;
      itemPtr += 1;
    }

    buffer->_queue_head_index = advanceIndex(buffer->_queue_head_index, buffer->_max_queue_size);

    buffer->_items_in_queue++;

    LOGGER("Added item to queue.")

    result = SUCCESS;
  }

THREAD_SAFE_END

  return result;
}

RESULT popItem( CircularBuffer * const buffer, void * const item)
{
THREAD_SAFE_BEGIN

  RESULT result;
  uint16_t index =0;

  uint8_t *bufferPtr;
  uint8_t *itemPtr;

  if( buffer == NULL )
  {
    LOGGER("Buffer pointer NULL; Not adding item");
    result = NULL_BUFFER_PTR;
  }
  else if( item == NULL )
  {
    LOGGER("Item pointer NULL; Not adding item");
    result = NULL_ITEM_PTR;
  }
  else if(buffer->_items_in_queue == 0)
  {
    LOGGER("Popping item failed. Queue empty.")
    result = QUEUE_EMPTY;
  }
  else
  {
    bufferPtr = ((uint8_t *)buffer->_buffer);
    itemPtr = ((uint8_t *)item);

    bufferPtr += ((buffer->_queue_tail_index) * buffer->_bytes_per_element);

    //Manually fill in all the buffer elements byte by byte
    for( index = 0; index < buffer->_bytes_per_element; index++)
    {
      *itemPtr = *bufferPtr;

      bufferPtr += 1;
      itemPtr += 1;
    }

    buffer->_queue_tail_index = advanceIndex(buffer->_queue_tail_index, buffer->_max_queue_size);

    buffer->_items_in_queue--;

    LOGGER("Popped item from queue.")

    result = SUCCESS;
  }

THREAD_SAFE_END

  return result;
}

uint8_t getNumberOfItemsInQueue(CircularBuffer * const buffer)
{
THREAD_SAFE_BEGIN

  uint8_t size = 0;

  if( buffer == NULL )
  {
    LOGGER("Buffer pointer NULL; Cannot get number of items.");
  }
  else
  {
    size = buffer->_items_in_queue;
  }

THREAD_SAFE_END

  return size;
}

