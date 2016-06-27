#ifndef EMBEDDED_CIRCULAR_BUFFER
#define EMBEDDED_CIRCULAR_BUFFER

#include <stdint.h>

//TODO: Remove to common
//BEGIN: User defined MACROS
#define LOGGER(MESSAGE) printf(MESSAGE);printf("\n");

#define THREAD_SAFE_BEGIN
#define THREAD_SAFE_END
//END: User defined MACROS


typedef struct circularBuffer
{
  const uint8_t maxQueueSize;

  const uint8_t bytesPerElement;
  uint8_t itemsInQueue;
  uint8_t queueHeadIndex;
  uint8_t queueTailIndex;

  void const *buffer; //pointer to buffer
}circularBuffer;

//declares buffer structure
#define declare_circular_buffer( BUFFER_NAME ) \
circularBuffer BUFFER_NAME;

//Allocates memory for buffer
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

typedef enum RESULT
{
  SUCCESS = 0,
  NULL_BUFFER_PTR = -1,
  NULL_ITEM_PTR = -2,
  QUEUE_FULL = -3,
  QUEUE_EMPTY = -4,
}RESULT;


void resetQueue(circularBuffer *thisBuffer);
RESULT addItem(circularBuffer *thisBuffer, const void *item);
RESULT popItem(circularBuffer *thisBuffer, void *item);
uint8_t getItemsInQueue(circularBuffer *thisBuffer);

#endif
