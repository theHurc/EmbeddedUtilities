#include <stdio.h>

#include "tableDrivenStateMachine.h"

int testFunction(void *contextData)
{
  printf("Here we go!\n");
  return 0;
}

bool testTriggerFunction(void *contextData)
{
  return true;
}

tableEntry stateTable[] = 
{
  {0, testFunction, testTriggerFunction, testFunction, 1},
  {1, testFunction, testTriggerFunction, testFunction, 0}
};

const int TABLE_SIZE = (sizeof(stateTable)/sizeof(stateTable[0]));


int main()
{
  printf("Top of main\n");

  int i = 0;

  stateMachine machine;

  machine.stateTable = stateTable;
  machine.tableSize = TABLE_SIZE;
  machine.currentState = 0;

  for(i = 0; i < 10; i++)
  {
    stateMachineEngine(&machine);
  }

  return 0;
}
