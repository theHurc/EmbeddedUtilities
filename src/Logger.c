#include "Logger.h"

#include <stdio.h>
#include <stdbool.h>

static bool isInitialized = false;
static LOGGING_LEVEL logging_level = DEBUG;

void initLogger()
{
  isInitialized = true;
}

void setLoggingLevel( LOGGING_LEVEL level )
{
  logging_level = level;
}


void logIt( LOGGING_LEVEL level, char *log )
{
  if( !isInitialized )
  {
    return;
  }

  if( level >= logging_level )
  {
    printf("%s\n", log);
  }
}

