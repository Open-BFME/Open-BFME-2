// Two more tiny ones: a masked flag read through two guards and an unsigned
// count turned into a scaled double. (The third, bfmeSetSign 0x00039880, now
// lives in its approved unit Code/Libraries/Source/debug/debug_cmd.cpp.)

#include "../../Include/GameNetwork/BfmeThingBW.h"

// ?bfmeMask@@YAHPAVBfmeThingBW@@@Z
int __cdecl bfmeMask(BfmeThingBW *thing)
{
	if (!thing)
		return 0;

	if (!thing->m_bfmeReady)
		return 0;

	return thing->m_bfmeFlags & 0x20;
}


// ?bfmeScale@@YANI@Z
double __cdecl bfmeScale(unsigned int value)
{
	return value * 0.001;
}
