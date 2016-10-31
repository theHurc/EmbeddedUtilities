#ifndef __COOPERATIVE_SCHEDULER__
#define __COOPERATIVE_SCHEDULER__

#include <stdint.h>

/*
 * Provides and interface for a task scheduler. There should only be one task
 * scheduler per system otherwise it doesn't really makes sense. All of the
 * internal structure assume there is just one.
 *
 * This idea is based on the description of "Time-Triggered Embedded Systems"
 * described here: http://www.safetty.net/download/pont_pttes_2014.pdf
 * I expanded this basic idea to be more generic and to provide additional
 * functionality that I've found useful in my experience.
 */

/*
 * Add a task to the scheduler to run periodically. Can only add period tasks
 * before starting the scheduler with schedulerStart()
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

//! Called from the timer interrupt to schedule the tasks. It's assumed that
//! this function gets called at the required interval.
void scheduleTasks( void );

#endif
