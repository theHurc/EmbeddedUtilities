#include "TimerInterrupt.h"
#include "TimerInterruptLinuxMock.h"

bool createTimerInterrupt( TimerInterrupt *timer )
{
  timer->setupTimerInterrupt = linuxMock_setupTimerInterrupt;
  timer->startTimer = linuxMock_startTimer;
  timer->disableTimerInterrupt = linuxMock_disableTimerInterrupt;
  timer->enableTimerInterrupt = linuxMock_reEnableTimerInterrupt;

  return true;
}
