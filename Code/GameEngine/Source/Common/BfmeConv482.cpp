// cl: /GF
// Native VA 00DD8310 points at the complete "ID" key at 00BED340.
// Keep the existing data-ledger name and ABI; the rowed addInt callee
// consumes the key as a C string.
void *g_bfmeWhatBKG = (void *)"ID";

class BfmeSubBKG;
#include "../../Include/GameNetwork/BfmeThingCIB.h"

void __stdcall bfmeGoBKG(BfmeSubBKG *sub, void *what)
{
	((BfmeThingCIB *)sub)->bfmeGoCIB(g_bfmeWhatBKG, what);
}
