// Source donor: EA BFME1 CommandLine.cpp parseSeed.
// BFME2 live -randomSeed table81FBD0 -> 3B9D2C (full51B).
// Unlike the donor: no global null guard, reset to zero with no value,
// and return1 on every path. atoi named IAT BBA624 independently verified.
// cl: /DNDEBUG /MD
#include <stdlib.h>
class GlobalData {
public:
    char prefix[0x1228];
    int m_fixedSeed;
};
extern GlobalData *TheWritableGlobalData;
int parseRandomSeed(char *args[],int num) {
    if(num>1) TheWritableGlobalData->m_fixedSeed=atoi(args[1]);
    else TheWritableGlobalData->m_fixedSeed=0;
    return 1;
}
