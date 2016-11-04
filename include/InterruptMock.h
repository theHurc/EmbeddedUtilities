#ifndef __INTERRUPT_MOCK__
#define __INTERRUPT_MOCK__

#include <stdint.h>
#include <stdbool.h>

/*
 * Functions for setting up a single interrupt to mock an interrupt in an
 * embedded system.
 *
 * Must link with -lrt
 */

bool setupTimerInterrupt( void (*callback)(int) );

bool disableTimerInterrupt( void );

bool enableTimerInterrupt( void );

bool startTimer( uint32_t interrupt_timer_ms );

#endif
