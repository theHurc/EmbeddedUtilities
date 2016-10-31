#include "XMacroTable.h"


//Build the array of structures with just the first three variables
#define X(A,B,C,D) {B, C},
const CMDS commandTable[] = { COMMAND_TABLE };
#undef X


