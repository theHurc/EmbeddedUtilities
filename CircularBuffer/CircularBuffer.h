#ifndef EMBEDDED_CIRCULAR_BUFFER
#define EMBEDDED_CIRCULAR_BUFFER

#include <stdint.h>

//BEGIN: User defined MACROS
#define LOGGER(x) printf(x);printf("\n");

#define MAX_ITEMS_IN_QUEUE 5
#define ITEM_TYPE uint8_t

#define THREAD_SAFE_BEGIN
#define THREAD_SAFE_END
//END: User defined MACROS


#define EMPTY 0

typedef enum RESULT
{
  SUCCESS = 0,
  QUEUE_FULL = -1,
  QUEUE_EMPTY = -2,
}RESULT;

typedef struct CircularBuffer
{
  ITEM_TYPE queue[MAX_ITEMS_IN_QUEUE];

  uint8_t itemsInQueue;
  uint8_t queueHeadIndex; //points to next slot to fill
  uint8_t queueTailIndex; //point to next slot to return

 }CircularBuffer;

RESULT initQueue(CircularBuffer *thisBuffer);
RESULT addItem(CircularBuffer *thisBuffer, const ITEM_TYPE *item);
RESULT popItem(CircularBuffer *thisBuffer, ITEM_TYPE *item);
uint8_t getQueueSize(CircularBuffer *thisBuffer);
//RESULT peekItem(CircularBuffer *thisBuffer, ITEM_TYPE *item);

#endif
