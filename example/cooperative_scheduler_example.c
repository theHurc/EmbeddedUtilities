#include "CooperativeScheduler.h"
#include "TimerInterrupt.h"
#include "TimerInterruptFactory.h"
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
  //schedulerScheduleTasks();
  printf("Something is happening");
}

int main()
{
  initLogger();

  TimerInterrupt timer;

  schedulerAddPeriodicTask(function_one, 0, 1000);
  //schedulerAddPeriodicTask(function_two, 0, 3500);

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
