#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct tableEntry
{
  uint16_t currentState;
  int (*entryFunction)(void *contextData);
  bool (*triggerFunction)(void *contextData);
  int (*exitFunction)(void *contextData);
  uint16_t nextState;
}tableEntry;

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

typedef struct stateMachine
{
  tableEntry *stateTable;
  uint16_t tableSize;
  uint16_t currentState;
  void *contextData;
}stateMachine;

int stateMachineEngine(stateMachine *machine)
{
  //static uint16_t currentState = 0;
  uint16_t i, r;

  printf("Current state: %d\n", machine->currentState);

  for(i = 0; i < machine->tableSize; i++)
  {
    if(machine->stateTable[i].currentState == machine->currentState)
    {
      if(machine->stateTable[i].triggerFunction(machine->contextData))
      {
        machine->stateTable[i].exitFunction(machine->contextData);
        machine->currentState = machine->stateTable[i].nextState;

        for(r = 0; r < machine->tableSize; r++)
        {
          if(machine->stateTable[r].currentState == machine->currentState)
          {
            machine->stateTable[r].entryFunction(machine->contextData);
            break;
          }
        }
        break;
      }
    }
  }

  return 0;
}

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
