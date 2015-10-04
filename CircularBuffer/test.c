#include "CircularBuffer.h"
#include "assert.h"

int main ()
{
  uint8_t i;

  uint8_t addNumber = 0;
  uint8_t popNumber = 0;

  CircularBuffer buffer;

//Queue status after init
  assert(initQueue(&buffer) == SUCCESS);
  assert(popItem(&buffer, &popNumber) == QUEUE_EMPTY);
  assert(getQueueSize(&buffer) == EMPTY);

//Add a single item
  addNumber = 15;
  assert(addItem(&buffer, &addNumber) == SUCCESS);
  assert(getQueueSize(&buffer) == 1);

//Remove a single item
  assert(popItem(&buffer, &popNumber) == SUCCESS);
  assert(popNumber == addNumber);
  assert(getQueueSize(&buffer) == EMPTY);

//Remove a single item from empty queue
  assert(popItem(&buffer, &popNumber) == QUEUE_EMPTY);
  assert(getQueueSize(&buffer) == EMPTY);

//fill up the queue
  addNumber = 0;

  for(i = 0; i < MAX_ITEMS_IN_QUEUE; i++)
  {
    addNumber++;
    assert(addItem(&buffer, &addNumber) == SUCCESS);
    assert(getQueueSize(&buffer) == addNumber);
  }

//Overfill queue
  addNumber = 110;
  assert(addItem(&buffer, &addNumber) == QUEUE_FULL);
  assert(getQueueSize(&buffer) == 5);

  addNumber = 120;
  assert(addItem(&buffer, &addNumber) == QUEUE_FULL);
  assert(getQueueSize(&buffer) == 5);

//empty queue
  addNumber = 0;
  //set to a different value than addNumber to check
  //for correct removal of the first element
  popNumber = 100;

  for(i = 0; i < MAX_ITEMS_IN_QUEUE; i++)
  {
    addNumber++;
    assert(popItem(&buffer, &popNumber) == SUCCESS);
    assert(popNumber == addNumber);
    assert(getQueueSize(&buffer) == (MAX_ITEMS_IN_QUEUE - addNumber));
  }

//Remove items from empty queue
  assert(popItem(&buffer, &popNumber) == QUEUE_EMPTY);
  assert(getQueueSize(&buffer) == EMPTY);

  assert(popItem(&buffer, &popNumber) == QUEUE_EMPTY);
  assert(getQueueSize(&buffer) == EMPTY);

  assert(popItem(&buffer, &popNumber) == QUEUE_EMPTY);
  assert(getQueueSize(&buffer) == EMPTY);

  assert(popItem(&buffer, &popNumber) == QUEUE_EMPTY);
  assert(getQueueSize(&buffer) == EMPTY);

  return 0;
}
