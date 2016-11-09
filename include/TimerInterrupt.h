#ifndef __TIMER_INTERRUPT__
#define __TIMER_INTERRUPT__

#include <stdint.h>
#include <stdbool.h>

/*
 * Basic interface for setting up a single timer interrupt. Obviously this there
 * are quite a few ways to expand this interface like setting up a way to poll
 * for the time, setting up more than one callback function, etc. But this
 * works for just a basic interface.
 */

/*
 * Initialzes all the timer parameters. Must be called before any of the other
 * timer related functions.
 */
bool setupTimerInterrupt( void (*callback)( void ) );

//! Start the timer with the provided interval
bool startTimer( uint32_t interrupt_timer_ms );

//! Temporarily disable the interrupt
bool disableTimerInterrupt( void );

//! Reenable timer interrupt
bool reEnableTimerInterrupt( void );


//Must mirror the above functions
typedef struct
{
  bool (*setupTimerInterrupt)( void (*callback)( void ) );
  bool (*startTimer)( uint32_t interrupt_timer_ms );
  bool (*disableTimerInterrupt)( void );
  bool (*enableTimerInterrupt)( void );
}TimerInterrupt;


#endif
