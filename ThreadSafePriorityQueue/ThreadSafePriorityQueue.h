#ifndef _THREAD_SAFE_PRIORITY_QUEUE_
#define _THREAD_SAFE_PRIORITY_QUEUE_

#include <stdint.h>

#define QUEUE_SIZE 10
#define QUEUE_CONTAINER_TYPE uint32_t

//higher priority is a lower number
//lower number is higher priority
typedef enum QUEUE_PRIORITIES
{
  VERY_HIGH = 0,
  HIGH,
  MEDIUM,
  LOW,
  VERY_LOW,

  NUMBER_OF_PRIORITIES, //placeholder
}QUEUE_PRIORITIES;

typedef struct QUEUE_ELEMENT
{
  QUEUE_PRIORITIES priority;
  QUEUE_CONTAINER_TYPE element;
}QUEUE_ELEMENT;

typedef enum QUEUE_RETURN_VALUES
{
  SUCCESS = 0,
  FAILED_TO_INIT = -1,
  QUEUE_FULL = -2,
}QUEUE_RETURN_VALUES;


int initQueue(void);
int addToQueue(const QUEUE_CONTAINER_TYPE *item, QUEUE_PRIORITIES priority);
//int size();
//void *popQueue();

#endif
