#ifndef EMBEDDED_CIRCULAR_BUFFER
#define EMBEDDED_CIRCULAR_BUFFER

#include <stdint.h>

/*
 * Structure that holds all variables related to a circular buffer.
 *
 * The pointer to buffer is of void const * type so the buffer
 * can be of generic type. Unfortunately, C doesn't provide a
 * concept of private variables but this structure's internals
 * shouldn't be touched by the client. The client should just pass
 * a pointer to the buffer for buffer operations.
 */
typedef volatile struct circularBuffer
{
  const uint8_t maxQueueSize;

  const uint8_t bytesPerElement;
  uint8_t itemsInQueue;
  uint8_t queueHeadIndex;
  uint8_t queueTailIndex;

  void * const buffer; //pointer to the actual buffer
}circularBuffer;

/*
 * Macro declaring buffer structure; Use in .h file make visable
 * to other files.
 */
#define declare_circular_buffer( BUFFER_NAME ) \
extern circularBuffer BUFFER_NAME;

/*
 * Macro that allocates and initializes memory for a buffer structure.
 *
 * BUFFER_NAME must be the same if using the above 'declare' macro.
 * Volatile because this may be used between the main application
 * and an interrupt.
 *
 * This maybe isn't obvious from the macro itself but this is actually
 * initializing each variable in the struct so it must be outside
 * any functions. (It's a compile time thing; not runtime.)
 */
#define define_circular_buffer( BUFFER_NAME, ITEM_TYPE, NUMBER_OF_ELEMENTS ) \
ITEM_TYPE buffer_##BUFFER_NAME[NUMBER_OF_ELEMENTS]; \
\
circularBuffer BUFFER_NAME = \
{ \
  .maxQueueSize = NUMBER_OF_ELEMENTS,  \
  .bytesPerElement = sizeof(ITEM_TYPE), \
  .itemsInQueue = 0, \
  .queueHeadIndex = 0, \
  .queueTailIndex = 0, \
\
  .buffer = &buffer_##BUFFER_NAME \
};

//! Possible return values for the public functions below
typedef enum RESULT
{
  SUCCESS = 0,
  NULL_BUFFER_PTR = -1,
  NULL_ITEM_PTR = -2,
  QUEUE_FULL = -3,
  QUEUE_EMPTY = -4,
}RESULT;

//Public functions

/*
 * Soft resets the queue to empty. Does not clear the
 * the associated buffer memory to 0.
 */
void resetQueue(circularBuffer * const thisBuffer);

/*
 * Adds an item to the queue if there is an available space.
 */
RESULT addItem(circularBuffer * const thisBuffer, const void *item);

/*
 * Removes the oldest item from the queue and returns in
 * 'item'.
 */
RESULT popItem(circularBuffer * const thisBuffer, void *item);

/*
 * Returns the number of items in queue.
 */
uint8_t getItemsInQueue(circularBuffer * const thisBuffer);

#endif
