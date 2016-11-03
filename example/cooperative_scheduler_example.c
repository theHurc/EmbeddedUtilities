#include "CooperativeScheduler.h"

#include <stdio.h>

void function_one( void )
{
  printf("Ran function one");
}

void function_two( void )
{
  printf("Ran function two");
}

void spoof_1ms_tick(void)
{
  //TODO:Add a timer thingy here
  schedulerScheduleTasks();
}

int main()
{
  schedulerAddPeriodicTask(function_one, 0, 1000);
  schedulerAddPeriodicTask(function_two, 0, 3500);

  schedulerStart();

  while(1)
  {
    spoof_1ms_tick();
    schedulerDispatchTasks();
  }

  return 0;
}
