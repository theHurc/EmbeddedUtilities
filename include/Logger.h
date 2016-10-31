#ifndef __LOGGER__
#define __LOGGER__

typedef enum LOGGING_LEVEL
{
  DEBUG = 0,
  COMMENT = 1,
  INFO = 2,
  WARN = 3,
  ERR = 4
}LOGGING_LEVEL;

//! Set up the logger; must be called before using the logger
void initLogger();

//! Set global logging level
void setLoggingLevel( LOGGING_LEVEL level );

//! Log only if the global logging level is at or below the message log level
void logIt( LOGGING_LEVEL level, char *log );

#endif
