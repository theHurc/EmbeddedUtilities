#ifndef __TIMER_INTERRUPT_LINUX_MOCK__
#define __TIMER_INTERRUPT_LINUX_MOCK__

#include "TimerInterrupt.h"

#include <stdint.h>
#include <stdbool.h>

/*
 * Linux implementation of a timer interrupt which mocks an embedded interrupt.
 * Implements TimerInterrupt found in TimerInterrupt.h
 *
 * Must link with -lrt
 */

bool linuxMock_setupTimerInterrupt( void (*callback)( void ) );

//! Start the timer with the provided interval
bool linuxMock_startTimer( uint32_t interrupt_timer_ms );

//! Temporarily disable the interrupt
bool linuxMock_disableTimerInterrupt( void );

//! Reenable timer interrupt
bool linuxMock_reEnableTimerInterrupt( void );

#endif
