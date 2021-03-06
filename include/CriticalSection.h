#ifndef __CRITICAL_SECTION__
#define __CRITICAL_SECTION__

//! Disables interrupts so shared data can be edited safely
void enterCriticalSection(void);

//! Enables interrupts so shared data can be edited safely
void exitCriticalSection(void);

#endif
