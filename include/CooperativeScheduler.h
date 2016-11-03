#ifndef __COOPERATIVE_SCHEDULER__
#define __COOPERATIVE_SCHEDULER__

#include <stdint.h>

/*
 * Cooperative Scheduler
 *
 * Provides and interface for a cooperative task scheduler. There should only be
 * one task scheduler per system otherwise it doesn't reall makes sense. All of
 * the internal structure assumes there is just one. A task schedules tasks
 * periodically and executes each of them to compeltion.
 *
 * This idea is based on the description of "Time-Triggered Embedded Systems"
 * described here: http://www.safetty.net/download/pont_pttes_2014.pdf
 * I expanded this basic idea to be more generic and to provide additional
 * functionality that I've found useful in my experience.
 */

/*
 * Add a task to the scheduler to run periodically.
 *
 * @param task  The function to execute when the task runs.
 * @param begin_time_ms  Delay time in ms before the first execution of the task
 * @param repeat_time_ms  Period in ms to run the task.
 */
void schedulerAddPeriodicTask( void (*task)(void),
                               uint32_t begin_time_ms,
                               uint32_t repeat_time_ms );

/*
 * Add task to the run scheduler for a single run
 *
 * @param task  The function to execute when the task runs.
 */
void schedulerAddOneShotTask( void (*task)(void) );

void schedulerInit( void );

//! Start the timer that will schedule the periodic tasks.
void schedulerStart( void );

//! Execute all the tasks in the task queue. Empties the queue completely.
void schedulerDispatchTasks( void );

//! Called from the timer interrupt to schedule the tasks. It's assumed that
//! this function gets called at the required interval.
void schedulerScheduleTasks( void );

#endif
