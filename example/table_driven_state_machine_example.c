#include <stdio.h>

#include "TableDrivenStateMachine.h"

void testFunction(void *contextData)
{
  printf("Here we go!\n");
  return;
}

bool testTriggerFunction(void *contextData)
{
  return true;
}

TableEntry stateTable[] = 
{
  {0, testFunction, testTriggerFunction, testFunction, 1},
  {1, testFunction, testTriggerFunction, testFunction, 0}
};

//TODO: Change this to happen in the macro
const int TABLE_SIZE = (sizeof(stateTable)/sizeof(stateTable[0]));

DEFINE_STATE_MACHINE( test_state_machine,
                      stateTable,
                      TABLE_SIZE,
                      0,
                      NULL )

int main()
{
  printf("Top of main\n");

  int i = 0;

  for(i = 0; i < 10; i++)
  {
    executeStateMachine(&test_state_machine);
  }

  return 0;
}
