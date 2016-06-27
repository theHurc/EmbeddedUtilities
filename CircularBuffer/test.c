#include "CircularBuffer.h"
#include "assert.h"
#include "stdio.h"
#include "limits.h"
#include "stdbool.h"

#define BUFFER_SIZE 5
#define STRUCT_BUFFER_SIZE 15

typedef struct TestStruct
{
  uint8_t unsigned8;
  int8_t signed8;
  uint16_t unsigned16;
  int16_t signed16;
  uint32_t unsigned32;
  int32_t signed32;
  uint64_t unsigned64;
  int64_t signed64;

  bool is;

  uint8_t *unsigned8Ptr;
  uint64_t *unsigned64Ptr;
}TestStruct;


define_circular_buffer(testBuffer, int, BUFFER_SIZE);
define_circular_buffer(testStructBuffer, TestStruct, STRUCT_BUFFER_SIZE);


bool compareTestStruct(TestStruct test1, TestStruct test2)
{
  if( (test1.unsigned8 == test1.unsigned8) &&
      (test1.signed8 == test1.signed8) &&
      (test1.unsigned16 == test1.unsigned16) &&
      (test1.signed16 == test1.signed16) &&
      (test1.unsigned32 == test1.unsigned32) &&
      (test1.signed32 == test1.signed32) &&
      (test1.unsigned64 == test1.unsigned64) &&
      (test1.signed64 == test1.signed64) &&
      (test1.is == test1.is) &&
      (test1.unsigned8Ptr == test1.unsigned8Ptr) &&
      (test1.unsigned64Ptr == test1.unsigned64Ptr) )
  {
    return true;
  }

  return false;
}

int main ()
{
  uint8_t i;

  int addNumber = 0;
  int popNumber = 0;

//Queue status at the beginning
  assert(popItem(&testBuffer, &popNumber) == QUEUE_EMPTY);
  assert(getItemsInQueue(&testBuffer) == 0);

//Add a single item
  addNumber = 15;
  assert(addItem(&testBuffer, &addNumber) == SUCCESS);
  assert(getItemsInQueue(&testBuffer) == 1);

//Remove a single item
  assert(popItem(&testBuffer, &popNumber) == SUCCESS);
  assert(popNumber == addNumber);
  assert(getItemsInQueue(&testBuffer) == 0);

//Remove a single item from empty queue
  assert(popItem(&testBuffer, &popNumber) == QUEUE_EMPTY);
  assert(getItemsInQueue(&testBuffer) == 0);

//fill up the queue
  addNumber = 0;

  for(i = 0; i < BUFFER_SIZE; i++)
  {
    addNumber++;
    assert(addItem(&testBuffer, &addNumber) == SUCCESS);
    assert(getItemsInQueue(&testBuffer) == addNumber);

  }

//Overfill queue
  addNumber = 110;
  assert(addItem(&testBuffer, &addNumber) == QUEUE_FULL);
  assert(getItemsInQueue(&testBuffer) == 5);

  addNumber = 120;
  assert(addItem(&testBuffer, &addNumber) == QUEUE_FULL);
  assert(getItemsInQueue(&testBuffer) == 5);

//empty queue
  addNumber = 0;
  //set to a different value than addNumber to check
  //for correct removal of the first element
  popNumber = 100;

  for(i = 0; i < BUFFER_SIZE; i++)
  {
    printf("Pop an item: %x\n", i);
    addNumber++;
    assert(popItem(&testBuffer, &popNumber) == SUCCESS);
    assert(popNumber == addNumber);
    assert(getItemsInQueue(&testBuffer) == (BUFFER_SIZE - addNumber));
  }

//Remove items from empty queue
  assert(popItem(&testBuffer, &popNumber) == QUEUE_EMPTY);
  assert(getItemsInQueue(&testBuffer) == 0);

//Add a few more items
  addNumber = 45903;
  assert(addItem(&testBuffer, &addNumber) == SUCCESS);
  addNumber = 255;
  assert(addItem(&testBuffer, &addNumber) == SUCCESS);

//Test with Null pointers
  assert(addItem(NULL, &addNumber) == NULL_BUFFER_PTR);
  assert(addItem(&testBuffer, NULL) == NULL_ITEM_PTR);

  assert(popItem(NULL, &addNumber) == NULL_BUFFER_PTR);
  assert(popItem(&testBuffer, NULL) == NULL_ITEM_PTR);

//Pop one more item
  assert(popItem(&testBuffer, &popNumber) == SUCCESS);
  assert(popNumber == 45903);
  assert(getItemsInQueue(&testBuffer) == 1);

//reset queue
  resetQueue(&testBuffer);
  assert(getItemsInQueue(&testBuffer) == 0);

//Add a few more items
  addNumber = INT_MAX;
  assert(addItem(&testBuffer, &addNumber) == SUCCESS);
  assert(getItemsInQueue(&testBuffer) == 1);
  assert(popItem(&testBuffer, &popNumber) == SUCCESS);
  assert(getItemsInQueue(&testBuffer) == 0);
  assert(popNumber == INT_MAX);

  addNumber = 255;
  assert(addItem(&testBuffer, &addNumber) == SUCCESS);
  assert(getItemsInQueue(&testBuffer) == 1);
  assert(popItem(&testBuffer, &popNumber) == SUCCESS);
  assert(getItemsInQueue(&testBuffer) == 0);
  assert(popNumber == 255);

//reset queue
  resetQueue(&testBuffer);
  assert(getItemsInQueue(&testBuffer) == 0);


//TestStruct tests

  TestStruct Anothertest;
  TestStruct Firsttest;
  TestStruct returnedTestStruct;

  Firsttest.unsigned8 = 0;
  Firsttest.signed8 = -90;
  Firsttest.unsigned16 = 7283;
  Firsttest.signed16 = -939;
  Firsttest.unsigned32 = 4000000;
  Firsttest.signed32 = -16839;
  Firsttest.unsigned64 = 10020202020;
  Firsttest.signed64 = -999900001;
  Firsttest.is = false;
  Firsttest.unsigned8Ptr = (uint8_t *)0x91010;
  Firsttest.unsigned64Ptr = (uint64_t *)0x0;

  Anothertest = Firsttest;

//Add some items
  assert(addItem(&testStructBuffer, &Anothertest) == SUCCESS);
  assert(addItem(&testStructBuffer, &Firsttest) == SUCCESS);
  assert(getItemsInQueue(&testStructBuffer) == 2);

//Remove the items
  assert(popItem(&testStructBuffer, &returnedTestStruct) == SUCCESS);
  assert(compareTestStruct(Anothertest, returnedTestStruct) == true);
  assert(getItemsInQueue(&testStructBuffer) == 1);

  assert(popItem(&testStructBuffer, &returnedTestStruct) == SUCCESS);
  assert(compareTestStruct(Anothertest, returnedTestStruct) == true);
  assert(getItemsInQueue(&testStructBuffer) == 0);

  assert(popItem(&testStructBuffer, &popNumber) == QUEUE_EMPTY);

  printf("\nTests passed!\n\n");

  return 0;
}
