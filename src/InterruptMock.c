#include "InterruptMock.h"
#include "Logger.h"

#include <stdbool.h>
#include <signal.h>
#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

static bool _timer_initialized = false;

static timer_t _timer_handle;

static struct itimerspec _timer_time;

static struct sigaction _signal_handler;

bool setupTimerInterrupt( void (*callback)(int) )
{
  struct sigevent configure_event;
  sigset_t mask;

  if( _timer_initialized )
  {
    LOG_WARN("Timer interrupt was already initialized. Reinitializing...");
    _timer_initialized = false;
  }

//Establish handler for timer interrupt
  _signal_handler.sa_flags = SA_SIGINFO;
  _signal_handler.sa_handler = callback;
  sigemptyset(&_signal_handler.sa_mask);

  if( sigaction ( SIGRTMIN, &_signal_handler, NULL ) < 0 )
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

bool startTimer( uint32_t interrupt_timer_ms )
{
  if( !_timer_initialized )
  {
    LOG_ERROR("Timer interrupt cannot be started before being setup.");
    return false;
  }

  //TODO: Fix this to take the parameter correctly
  _timer_time.it_interval.tv_sec = 1;
  _timer_time.it_interval.tv_nsec = 0;

  _timer_time.it_value.tv_sec = 1;
  _timer_time.it_value.tv_nsec = 0;

  if( timer_settime( _timer_handle, 0, &_timer_time, NULL ) < 0 )
  {
    LOG_ERROR("Setting up the timer failed.");
    return false;
  }

  return true;
}

bool disableTimerInterrupt( void )
{

  sigset_t mask;

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

bool enableTimerInterrupt( void )
{
  sigset_t mask;

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

