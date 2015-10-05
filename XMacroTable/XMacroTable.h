#ifndef X_MACRO_TABLE
#define X_MACRO_TABLE

//The actual table
#define COMMAND_TABLE \
  X(RUN,   "Run",   "Channel", 12) \
  X(PAUSE, "Pause", "Channel", 13)

//Build the enum of the indexes (the first paramter in the table)
#define X(A,B,C,D) A,
typedef enum INDEX { COMMAND_TABLE } INDEX;
#undef X

//Structure of just the first three table parameters 
typedef struct CMDS
{
  char *commandName;
  char *paramterOneName;
}CMDS;

//Structure of just the index and last table parameters
typedef struct CMDS_EXTENDED
{
  int extendedVariable;
}CMDS_EXTENDED;

extern const CMDS_EXTENDED commandTableExtended[];
extern const CMDS commandTable[];

#endif
