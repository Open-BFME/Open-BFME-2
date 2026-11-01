// Source donor: EA BFME1 CommandLine.cpp parseSeed.
// BFME2 live -randomSeed table81FBD0 -> 3B9D2C (full51B).
// Unlike the donor: no global null guard, reset to zero with no value,
// and return1 on every path. atoi named IAT BBA624 independently verified.
// cl: /DNDEBUG /MD
#include <stdlib.h>
#include "../../Include/Common/GlobalData.h"
extern GlobalData *TheWritableGlobalData;
int parseRandomSeed(char *args[],int num) {
    if(num>1) TheWritableGlobalData->field1228=atoi(args[1]);
    else TheWritableGlobalData->field1228=0;
    return 1;
}
