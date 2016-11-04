#include "InterruptMock.h"
#include "Logger.h"

#include <stdio.h>
#include <unistd.h>

void IRQ( int signal )
{
  printf("In the interrupt.\n");
}

int main(int argc, char **argv)
{
  int i;

  initLogger();

  printf("Here 1\n");

  if( !setupTimerInterrupt( IRQ ) )
  {
    return 1;
  }

  printf("Here 2\n");

  if( !startTimer(1) )
  {
    return 1;
  }

  printf("Here 3\n");

  for( i = 0; i < 100; i++ )
  {
    usleep(100000);
  }
  
  if( !disableTimerInterrupt() )
  {
    return 1;
  }

  for( i = 0; i < 100; i++ )
  {
    usleep(100000);
  }

  if( !enableTimerInterrupt() )
  {
    return 1;
  }

  for( i = 0; i < 100; i++ )
  {
    usleep(100000);
  }

  return 0;
}
