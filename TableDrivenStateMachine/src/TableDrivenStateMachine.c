#include <stdio.h>

#include "TableDrivenStateMachine/TableDrivenStateMachine.h"

void executeStateMachine(StateMachine * const machine)
{
  uint8_t i, r;

  printf("Current state: %d\n", machine->_current_state);

  for(i = 0; i < machine->_table_size; i++)
  {
    if(machine->_state_table[i].current_state == machine->_current_state)
    {
      if(machine->_state_table[i].trigger_function(machine->_context_data))
      {
        machine->_state_table[i].exit_function(machine->_context_data);
        machine->_current_state = machine->_state_table[i].next_state;

        for(r = 0; r < machine->_table_size; r++)
        {
          if(machine->_state_table[r].current_state == machine->_current_state)
          {
            machine->_state_table[r].entry_function(machine->_context_data);
            break;
          }
        }
        break;
      }
    }
  }

  return;
}
