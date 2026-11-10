// cl: /Ireference/shims/bfmerendobj /G7 /DNDEBUG /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep

// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
#include "../../../../GameEngine/Include/Common/BfmeVciAnchorElem.h"
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "systimer.h"

extern bool __identifier("?is_init@?1??Get@SysTimeClass@@QAEKXZ@4_NA");

SysTimeClass SystemTime;


SysTimeClass::SysTimeClass(void) :
	StartTime(0),
	WrapAdd(0)
{
	//tell windows we need single ms precision.
	timeBeginPeriod(1);
}

SysTimeClass::~SysTimeClass(void)
{
	//tell windows we need single ms precision.
	timeEndPeriod(1);
}

void SysTimeClass::Reset(void)
{
	StartTime = timeGetTime();
	WrapAdd = 0 - StartTime;
}


bool SysTimeClass::Is_Getting_Late(void)
{
	/*
	** Even though the timers are all unsigned so we have a max time of 0xffffffff the game casts it to int in various places
	** so it's safer to assume a signed max value.
	*/
	if (!__identifier("?is_init@?1??Get@SysTimeClass@@QAEKXZ@4_NA")) {
		Reset();
		__identifier("?is_init@?1??Get@SysTimeClass@@QAEKXZ@4_NA") = true;
	}
	unsigned long now = timeGetTime();
	unsigned long elapsed;
	if (now > StartTime) elapsed = now - StartTime;
	else elapsed = now + WrapAdd;
	if (elapsed > 0x6fffffff) {
		return(true);
	}
	return(false);
}

