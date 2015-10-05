#include "XMacroTable.h"


//Build a table that extends the command table
#define X(A,B,C,D) {D},
const CMDS_EXTENDED commandTableExtended[] = { COMMAND_TABLE };
#undef X
