#include "TimerInterrupt.h"
#include "TimerInterruptFactory.h"
#include "Logger.h"

#include <stdio.h>
#include <unistd.h>

void IRQ( void )
{
  printf("In the interrupt.\n");
}

int main(int argc, char **argv)
{
  int i;
  TimerInterrupt timer;

  initLogger();

  if( !createTimerInterrupt( &timer ) )
  {
    printf("Failed to create timer");
    return 1;
  }

  if( !timer.setupTimerInterrupt( IRQ ) )
  {
    printf("Could not set up timer");
    return 1;
  }

  if( !timer.startTimer(1000) )
  {
    printf("Could not start the timer.");
    return 1;
  }

  for( i = 0; i < 100; i++ )
  {
    usleep(100000);
  }
  
  if( !timer.disableTimerInterrupt() )
  {
    return 1;
  }

  for( i = 0; i < 100; i++ )
  {
    usleep(100000);
  }

  if( !timer.enableTimerInterrupt() )
  {
    return 1;
  }

  for( i = 0; i < 100; i++ )
  {
    usleep(100000);
  }

  return 0;
}
