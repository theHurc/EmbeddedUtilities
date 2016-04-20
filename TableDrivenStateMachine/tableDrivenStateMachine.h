#ifndef _TABLE_DRIVEN_STATE_MACHINE_H_
#define _TABLE_DRIVEN_STATE_MACHINE_H_

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

typedef struct stateMachine
{
  tableEntry *stateTable;
  uint16_t tableSize;
  uint16_t currentState;
  void *contextData;
}stateMachine;

int executeStateMachine(stateMachine *machine);

#endif
