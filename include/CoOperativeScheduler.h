#ifndef __CO_OPERATIVE_SCHEDULER__
#define __CO_OPERATIVE_SCHEDULER__

/*
 * Add a task to the scheduler to run periodically.
 *
 * @param task  The function to execute when the task runs.
 * @param begin_time_ms  Delay time in ms before the first execution of the task
 * @param repeat_time_ms  Period in ms to run the task
 */
void schedulerAddTask( void (*task)(void),
                       uint32_t begin_time_ms,
                       uint32_t repeat_time_ms );

//! Start the timer that will schedule the tasks periodically.
void schedulerStart( void );

//! Execute all the tasks in the task queue. Empties the queue completely.
void schedulerDispatchTasks( void );

//! Called from the timer interrupt to schedule the tasks
void scheduleTasks( uint32_t ms);

#endif
