#ifndef _TABLE_DRIVEN_STATE_MACHINE_H_
#define _TABLE_DRIVEN_STATE_MACHINE_H_

#include <stdint.h>
#include <stdbool.h>

typedef const struct TableEntry
{
  uint8_t current_state;
  void (*entry_function)(void * const context_data);
  bool (*trigger_function)(void * const context_data);
  void (*exit_function)(void * const context_data);
  uint8_t next_state;
}TableEntry;

typedef struct StateMachine
{
  const TableEntry * const _state_table;
  const uint8_t _table_size;
  uint8_t _current_state;
  void * const _context_data;
}StateMachine;

/*
 * Macro that allocates and initializes memory for a state machine.
 *
 * BUFFER_NAME must be the same if using the above 'DECLARE_CIRCULAR_BUFFER'
 * macro.
 *
 * This maybe isn't obvious from the macro itself but this is actually
 * initializing each variable in the struct as well as statically allocating
 * memory for the buffer so it must be outside any functions.
 *
 * @param STATE_MACHINE_NAME  The name of the state machine; basically the file
 *                            handle name used for state machine calls
 * @param TABLE_NAME  A pointer to a table of TableEntry values
 * @param TABLE_SIZE  The size of the table array given in TABLE_NAME in uint8_t
 * @param START_STATE  The starting state of this state machine in uint8_t
 * @param POINTER_TO_CONTEXT_DATA  A pointer to data for this state machine used
 *                                 as void * to support generic context data
 */
#define DEFINE_STATE_MACHINE( STATE_MACHINE_NAME, \
                              TABLE_NAME, \
                              START_STATE, \
                              POINTER_TO_CONTEXT_DATA ) \
StateMachine STATE_MACHINE_NAME = \
{ \
  ._state_table = TABLE_NAME, \
  ._table_size = (sizeof(TABLE_NAME)/sizeof(TABLE_NAME[0])), \
  ._current_state = START_STATE, \
  ._context_data = POINTER_TO_CONTEXT_DATA \
};


void executeStateMachine(StateMachine * const machine);

#endif
