// cl: /Oy- /MD
// platformsdk
//
// DebugAllocMemory, retail 0x0003E450, 83 bytes.
// Same GlobalAlloc + DCRASH_RELEASE arm as ProfileAllocMemory; this copy
// keeps the ebp frame retail uses for the size argument.

#include <windows.h>

#include "../../../GameEngine/Source/Common/debug.h"

extern Debug *theDebug;  // defined in DebugPreStaticInit.cpp

void *DebugAllocMemory(unsigned int numBytes)
{
	HGLOBAL h = GlobalAlloc(0, numBytes);
	if (!h)
	{
		Debug::SkipNext(true);
		theDebug->SkipNext();
		(theDebug->CrashBegin(0, 0, 0) << "Debug mem alloc failed").CrashDone(true);
	}
	return h;
}
