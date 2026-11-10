// cl: /Oy- /MD
// platformsdk
//
// ?DebugReAllocMemory@@YAPAXPAXI@Z, retail 0x0003E4B0, 189 bytes.
// Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug/debug_internal.cpp,
// DebugReAllocMemory): BFME2 crash arm is theDebug->SkipNext/CrashBegin/
// operator<</CrashDone over the Debug manager at 0x00DE0880 (same shape as
// the landed DebugAllocMemory TU in this directory); the recordCallsite is
// Debug::SkipNext(bool) at 0x00038790 (pinned).

#include <windows.h>
#include <string.h>


#include "../../../GameEngine/Source/Common/debug.h"

extern Debug *theDebug;  // defined in DebugPreStaticInit.cpp

void *DebugAllocMemory(unsigned int numBytes);

// ?DebugReAllocMemory@@YAPAXPAXI@Z
void *DebugReAllocMemory(void *oldPtr, unsigned int newSize)
{
	// Windows doesn't like ReAlloc with NULL handle/ptr...
	if (!oldPtr)
		return newSize ? DebugAllocMemory(newSize) : 0;

	// Shrinking to 0 size is basically freeing memory
	if (!newSize)
	{
		GlobalFree(oldPtr);
		return 0;
	}

	// now try GlobalReAlloc first
	void *h = GlobalReAlloc(oldPtr, newSize, 0);
	if (!h)
	{
		// this failed (Windows doesn't like ReAlloc'ing larger
		// fixed memory blocks) - go with Alloc/Free instead
		h = GlobalAlloc(0, newSize);
		if (!h)
		{
			Debug::SkipNext(true);
			theDebug->SkipNext();
			(theDebug->CrashBegin(0, 0, 0) << "Debug mem realloc failed").CrashDone(true);
		}
		unsigned int oldSize = GlobalSize(oldPtr);
		memcpy(h, oldPtr, oldSize < newSize ? oldSize : newSize);
		GlobalFree(oldPtr);
	}

	return h;
}
