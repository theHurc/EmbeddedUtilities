#include "CooperativeScheduler.h"
#include "ThreadSafeCircularBuffer.h"
#include "CriticalSection.h"
#include "Logger.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#define NUMBER_OF_PERIODIC_TASKS 5
#define TASK_QUEUE_SIZE 10

static bool _scheduler_started = false;
static uint8_t _period_tasks_in_scheduler = 0;


typedef struct TaskData
{
  void (*_task)(void);
  uint32_t _ticks_til_next_run;
  uint32_t _task_period;
}TaskData;

TaskData _task_data[NUMBER_OF_PERIODIC_TASKS];

typedef void (*task_pointer)(void);

//! A circular buffer of function pointers
DEFINE_CIRCULAR_BUFFER( _task_buffer, task_pointer, TASK_QUEUE_SIZE )


void schedulerAddTask( void (*task)(void),
                       uint32_t begin_time_ms,
                       uint32_t repeat_time_ms )
{
  if(_scheduler_started)
  {
    LOG_ERROR("Cannot add task to scheduler after it's already started.");
    return;
  }

  if( _period_tasks_in_scheduler < NUMBER_OF_PERIODIC_TASKS )
  {
    LOG_INFO("Adding a task to scheduler");
    _task_data[_period_tasks_in_scheduler]._task = task;
    _task_data[_period_tasks_in_scheduler]._ticks_til_next_run = begin_time_ms;
    _task_data[_period_tasks_in_scheduler]._task_period = repeat_time_ms;

    _period_tasks_in_scheduler++;
  }
  else
  {
    LOG_ERROR("Could not add task! Task buffer full.");
  }
}

void schedulerStart( void )
{
  LOG_INFO("Starting the scheduler");

  _scheduler_started = true;

  //TODO: start the timer
}

void schedulerDispatchTasks( void )
{
  void (*next_task)(void) = NULL;

  if(!_scheduler_started)
  {
    LOG_ERROR("Scheduler not started.");
    return;
  }

  //TODO: figure out where the critical sections need to go
  //enterCriticalSection();
  //exitCriticalSection();
  
  while( getNumberOfItemsInQueue( &_task_buffer ) > 0 )
  {
    if(  popItem( &_task_buffer, (void *)next_task ) == SUCCESS )
    {
      next_task();
    }
  }

}

void scheduleTasks( void )
{
  uint8_t i;

  if(!_scheduler_started)
  {
    LOG_ERROR("Scheduler not started.");
    return;
  }

//TODO: figure out where the critical sections need to go
  for(i = 0; i < _period_tasks_in_scheduler; i++)
  {
    if( _task_data[i]._ticks_til_next_run > 0 )
    {
      _task_data[i]._ticks_til_next_run--;
    }

    if( _task_data[i]._ticks_til_next_run == 0 )
    {
      addItem( &_task_buffer, _task_data[i]._task );
      _task_data[i]._ticks_til_next_run = _task_data[i]._task_period;
    }
  }

}

