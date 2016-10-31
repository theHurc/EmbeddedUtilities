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
typedef struct CircularBuffer
{
  const uint8_t _max_queue_size;

  const uint8_t _bytes_per_element;
  uint8_t _items_in_queue;
  uint8_t _queue_head_index;
  uint8_t _queue_tail_index;

  void * const _buffer; //pointer to the actual buffer
}CircularBuffer;

/*
 * Macro declaring buffer structure; Use in .h file make visable
 * to other files.
 */
#define DECLARE_CIRCULAR_BUFFER( BUFFER_NAME ) \
extern CircularBuffer BUFFER_NAME;

/*
 * Macro that allocates and initializes memory for a buffer structure.
 *
 * BUFFER_NAME must be the same if using the above 'DECLARE_CIRCULAR_BUFFER'
 * macro.
 *
 * This maybe isn't obvious from the macro itself but this is actually
 * initializing each variable in the struct as well as statically allocating
 * memory for the buffer so it must be outside any functions.
 */
#define DEFINE_CIRCULAR_BUFFER( BUFFER_NAME, ITEM_TYPE, NUMBER_OF_ELEMENTS ) \
ITEM_TYPE buffer_##BUFFER_NAME[NUMBER_OF_ELEMENTS]; \
\
CircularBuffer BUFFER_NAME = \
{ \
  ._max_queue_size = NUMBER_OF_ELEMENTS,  \
  ._bytes_per_element = sizeof(ITEM_TYPE), \
  ._items_in_queue = 0, \
  ._queue_head_index = 0, \
  ._queue_tail_index = 0, \
\
  ._buffer = &buffer_##BUFFER_NAME \
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
 *
 * @param buffer  The buffer to reset
 */
void resetQueue(CircularBuffer * const buffer);

/*
 * Adds an item to the end of the queue if there is an available space.
 *
 * @param buffer  The buffer to add an item
 * @param item  Pointer to item to add
 * @return  Result of the operation
 */
RESULT addItem(CircularBuffer * const buffer, const void * const item);

/*
 * Removes the item from the front of the queue if an item is available
 *
 * @param buffer  The buffer to remove an item
 * @param item  Contains the item removed from the front of the queue if
 *              there was an item to remove. Undefined otherwise.
 * @return  Result of the operation; item is only valid if return was SUCCESSFUL
 */
RESULT popItem(CircularBuffer * const buffer, void * const item);

/*
 * Returns the number of items in queue.
 */
uint8_t getNumberOfItemsInQueue(CircularBuffer * const buffer);

#endif
