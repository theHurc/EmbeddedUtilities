#include <stdio.h>

#include "tableDrivenStateMachine.h"

int initMachine(stateMachine *machine,
                tableEntry *stateTable,
                uint16_t tableSize,
                uint16_t startState,
                void *contextData )
{
  machine->stateTable = stateTable;
  machine->tableSize = tableSize;
  machine->currentState = startState;
  machine->contextData = contextData;
}

int executeStateMachine(stateMachine *machine)
{
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
