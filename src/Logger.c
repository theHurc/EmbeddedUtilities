#include "Logger.h"

#include <stdio.h>
#include <stdbool.h>

static bool isInitialized = false;

void initLogger(void)
{
  isInitialized = true;
}

void logIt( uint8_t level, char *log )
{
  if( !isInitialized )
  {
    return;
  }

  printf("%d: %s\n", level, log);
}

