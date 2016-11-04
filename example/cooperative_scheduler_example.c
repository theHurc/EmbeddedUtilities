#include "CooperativeScheduler.h"
#include "InterruptMock.h"
#include "Logger.h"

#include <stdio.h>
#include <unistd.h>

void function_one( void )
{
  printf("Ran function one");
}

void function_two( void )
{
  printf("Ran function two");
}

void spoof_1ms_tick(int signal)
{
  //TODO:Add a timer thingy here
  schedulerScheduleTasks();
  printf("I'm printing something, baby!\n");
}

int main()
{
  initLogger();

  schedulerAddPeriodicTask(function_one, 0, 1000);
  schedulerAddPeriodicTask(function_two, 0, 3500);

  setupTimerInterrupt(spoof_1ms_tick);

  schedulerStart();
  startTimer(1);

  while(1)
  {
    disableTimerInterrupt();
    schedulerDispatchTasks();
    enableTimerInterrupt();
    usleep(100000);
  }

  return 0;
}
