#include "TimerInterrupt.h"
#include "Logger.h"

#include <stdbool.h>
#include <signal.h>
#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

//Private variables
static timer_t _timer_handle;
static bool _timer_initialized = false;
static void (*_callback_handle)( void ) = NULL;

static void linuxCallback( int sig )
{
  //ignore the int
  if(_callback_handle == NULL)
  {
    return;
  }

  _callback_handle();
}

bool linuxMock_setupTimerInterrupt( void (*callback)( void ) )
{
  struct sigevent configure_event;
  struct sigaction signal_handler;
  sigset_t mask;

  if( _timer_initialized )
  {
    LOG_WARN("Timer interrupt was already initialized.");
    return false;
  }

//Establish handler for timer interrupt
  _callback_handle = callback;

  signal_handler.sa_flags = SA_SIGINFO;
  signal_handler.sa_handler = linuxCallback;
  sigemptyset(&signal_handler.sa_mask);

  if( sigaction ( SIGRTMIN, &signal_handler, NULL ) < 0 )
  {
    LOG_ERROR("Setting up signal handler failed.");
    return false;
  }

//Block the signal temporarily
  sigemptyset(&mask);
  sigaddset(&mask, SIGRTMIN);
  if( sigprocmask(SIG_SETMASK, &mask, NULL) < 0 )
  {
    LOG_ERROR("Blocking the signal temporarily failed.");
    return false;
  }

//Create the timer
  configure_event.sigev_notify = SIGEV_SIGNAL;
  configure_event.sigev_signo = SIGRTMIN;
  configure_event.sigev_value.sival_ptr = &_timer_handle;

  if( timer_create( CLOCK_REALTIME, &configure_event, &_timer_handle ) < 0 )
  {
    LOG_ERROR("Timer creation failed.");
    return false;
  }

//Unblock to interrupt
  if ( sigprocmask(SIG_UNBLOCK, &mask, NULL) < 0 )
  {
    LOG_ERROR("Unable to unblock signal.");
    return false;
  }

  _timer_initialized = true;

  return true;
}

bool linuxMock_startTimer( uint32_t interrupt_timer_ms )
{
  struct itimerspec timer_time;
  uint32_t seconds_portion = 0;

  if( !_timer_initialized )
  {
    LOG_ERROR("Timer interrupt cannot be started before being setup.");
    return false;
  }

  while( interrupt_timer_ms >= 1000 )
  {
    seconds_portion++;
    interrupt_timer_ms -= 1000;
  }
  
  timer_time.it_interval.tv_sec = seconds_portion;
  timer_time.it_interval.tv_nsec = interrupt_timer_ms * 1000000;

  timer_time.it_value.tv_sec = seconds_portion;
  timer_time.it_value.tv_nsec = interrupt_timer_ms * 1000000;

  if( timer_settime( _timer_handle, 0, &timer_time, NULL ) < 0 )
  {
    LOG_ERROR("Setting up the timer failed.");
    return false;
  }

  return true;
}

bool linuxMock_disableTimerInterrupt( void )
{
  sigset_t mask;

  if( !_timer_initialized )
  {
    LOG_ERROR("Timer interrupt cannot be disabled before being setup.");
    return false;
  }

  //Block the signal temporarily
  sigemptyset(&mask);
  sigaddset(&mask, SIGRTMIN);
  if( sigprocmask(SIG_SETMASK, &mask, NULL) < 0 )
  {
    LOG_ERROR("Blocking the signal temporarily failed.");
    return false;
  }

  return true;
}

bool linuxMock_reEnableTimerInterrupt( void )
{
  sigset_t mask;

  if( !_timer_initialized )
  {
    LOG_ERROR("Timer interrupt cannot be re-enabled before being setup.");
    return false;
  }

//Unblock the signal
  sigemptyset(&mask);
  sigaddset(&mask, SIGRTMIN);

  if ( sigprocmask(SIG_UNBLOCK, &mask, NULL) < 0 )
  {
    LOG_ERROR("Unable to unblock signal.");
    return false;
  }

  return true;
}

