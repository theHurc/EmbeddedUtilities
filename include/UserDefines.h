#ifndef EMBEDDED_USER_DEFINES
#define EMBEDDED_USER_DEFINES

#define LOGGER(MESSAGE) printf(MESSAGE);printf("\n");

//These must be function calls to prevent optimizer reordering
#define THREAD_SAFE_BEGIN
#define THREAD_SAFE_END

#endif
