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
  tableEntry stateTable[];
  uint16_t currentState;
  void *contextData;
}stateMachine;

int stateMachineEngine(void *contextData)
{
  static uint16_t currentState = 0;
  uint16_t i, r;

  printf("Current state: %d\n", currentState);

  for(i = 0; i < TABLE_SIZE; i++)
  {
    if(stateTable[i].currentState == currentState)
    {
      if(stateTable[i].triggerFunction(contextData))
      {
        stateTable[i].exitFunction(contextData);
        currentState = stateTable[i].nextState;

        for(r = 0; r < TABLE_SIZE; r++)
        {
          if(stateTable[r].currentState == currentState)
          {
            stateTable[r].entryFunction(contextData);
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

  for(i = 0; i < 10; i++)
  {
    stateMachineEngine(&i);
  }

  return 0;
}
