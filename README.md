# EmbeddedUtilities
Useful utilities for embedded systems written in C (no dynamic memory allocation)


#X Macros

##Motivation
In the past I have constructed command tables, state machine tables and whatever
other tables I needed using an array of structures and a corresponding enum to
index into the table like this:

```
typedef enum INDEX
{
  RUN,
  PAUSE,
}INDEX;

typedef struct CMDS
{
  INDEX index;
  char *commandName;
  char *parameterOneName;
  void (*execute)(void);
}CMDS;

const CMDS commandTable[]
{
  { RUN,   (char *)"Run",   (char *)"Channel", executeRun   },
  { PAUSE, (char*)"Pause",  (char *)"Channel", executePause },
};
```

The idea is that commandTable[RUN] could be used in the application code and if
the table changes in any way the index will change accordingly and the
application code doesn't need to change. This, however, requires keeping the
INDEX enum and the commandTable synchronized which is absolutely ripe for bugs
not to mention a maintenance nightmare!

##A solution
I have been searching for a solution to this problem for quite awhile and I
finally found X Macros! This solution has been around since the '60s but
apparently not many people know about it. More info on wikipedia here:

```
https://en.wikipedia.org/wiki/X_Macro
```

I was unable to make X Macro tables generic in a reasonable, understandable way
so the files in this folder just provide an example of how to use X Macros to
solve this problem.

Additionally, I ran into an issue recently where I needed to extend an existing
table in another file because of dependency issues. I have also included an
example to use X Macros to extend a table.

