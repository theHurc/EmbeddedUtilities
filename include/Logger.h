#ifndef __LOGGER__
#define __LOGGER__

#include <stdint.h>
/*
 * Lightweight logger. Based on macros so that depending on the logging level
 * the code can be compiled out.
 *
 * Can be compiled with '-DLOGGING_LEVEL=DEBUG' or whatever level is required
 */

#define DEBUG 1
#define INFO 2
#define WARN 3
#define ERROR 4

//setup the default logging level if not already defined in the compilation
#ifndef LOGGING_LEVEL
  #define LOGGING_LEVEL WARN
#endif

#if LOGGING_LEVEL == DEBUG
  #define LOG_DEBUG(LOG) logIt(DEBUG,LOG);
  #define LOG_INFO(LOG) logIt(INFO,LOG);
  #define LOG_WARN(LOG) logIt(WARN,LOG);
  #define LOG_ERROR(LOG) logIt(ERROR,LOG);
#elif LOGGING_LEVEL == INFO
  #define LOG_DEBUG(LOG)
  #define LOG_INFO(LOG) logIt(INFO,LOG);
  #define LOG_WARN(LOG) logIt(WARN,LOG);
  #define LOG_ERROR(LOG) logIt(ERROR,LOG);
#elif LOGGING_LEVEL == WARN
  #define LOG_DEBUG(LOG)
  #define LOG_INFO(LOG)
  #define LOG_WARN(LOG) logIt(WARN,LOG);
  #define LOG_ERROR(LOG) logIt(ERROR,LOG);
#elif LOGGING_LEVEL == ERROR
  #define LOG_DEBUG(LOG)
  #define LOG_INFO(LOG)
  #define LOG_WARN(LOG)
  #define LOG_ERROR(LOG) logIt(ERROR,LOG);
#else
  #error "LOGGING_LEVEL must be set to either DEBUG, INFO, WARN, or ERROR"
#endif


//! Set up the logger; must be called before using the logger
void initLogger();

//! Log only if the global logging level is at or below the message log level
void logIt( uint8_t level, char *log );

#endif
