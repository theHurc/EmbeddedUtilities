#include <stdio.h>
#include "XMacroTable.h"

//Demonstration of using X Macro tables
int main()
{
  printf("%s\n", commandTable[RUN].commandName);
  printf("%s\n", commandTable[PAUSE].commandName);

  printf("%s\n", commandTable[RUN].paramterOneName);
  printf("%s\n", commandTable[PAUSE].paramterOneName);

  printf("%d\n", commandTableExtended[RUN].extendedVariable);
  printf("%d\n", commandTableExtended[PAUSE].extendedVariable);

  return 0;
}
