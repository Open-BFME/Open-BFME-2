// cl: /DNDEBUG /MD /EHs-c- /Oy-
// platformsdk
//
// Debug::frameStatus, retail 0x0003A6A0 (175 bytes).
// Ported from Open-BFME-1 WWDebug/Debug_frameStatus.cpp: fast-path check at
// disableAssertsEtc +0x9DF8, critical section 0x00DE0884, curStackFrame +0x14 records the address,
// hash lookup, reset clears status, 2/3 means already decided, lazy
// UpdateFrameStatus when Unknown, true only for status 1.
// Dedicated TU with frame pointer (retail has ebp frame).

#include <windows.h>

struct DebugCriticalSection;
extern DebugCriticalSection g_bfmeCsDWC;

#include "../../../../GameEngine/Source/Common/debug.h"

// LookupFrame is frameless at retail RVA 0x00038330.
#pragma optimize("y", on)

// ?LookupFrame@Debug@@AAEPAUFrameHashEntry@1@I@Z
__forceinline Debug::FrameHashEntry *Debug::LookupFrame(unsigned int address)
{
	for (FrameHashEntry *entry = frameHash[address % FRAME_HASH_SIZE]; entry;
		entry = entry->next)
	{
		if (entry->frameAddr == address)
			return entry;
	}
	return 0;
}

// The matched caller retains its frame pointer.
#pragma optimize("y", off)

// ?frameStatus@Debug@@UAE_NI_N@Z
bool Debug::frameStatus(unsigned int address, bool reset)
{
	if (disableAssertsEtc != 0)
		return true;

	EnterCriticalSection((CRITICAL_SECTION *)&g_bfmeCsDWC);
	curStackFrame = address;
	FrameHashEntry *entry = LookupFrame(address);
	if (reset)
	{
		if (entry != 0)
			entry->status = Unknown;
		LeaveCriticalSection((CRITICAL_SECTION *)&g_bfmeCsDWC);
		return false;
	}
	if (entry == 0)
	{
		LeaveCriticalSection((CRITICAL_SECTION *)&g_bfmeCsDWC);
		return false;
	}
	if (entry->status == 2 || entry->status == 3)
	{
		LeaveCriticalSection((CRITICAL_SECTION *)&g_bfmeCsDWC);
		return false;
	}
	if (entry->status == Unknown)
		UpdateFrameStatus(*entry);
	LeaveCriticalSection((CRITICAL_SECTION *)&g_bfmeCsDWC);
	return entry->status == 1;
}
