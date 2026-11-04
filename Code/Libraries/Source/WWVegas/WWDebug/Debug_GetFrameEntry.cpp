// cl: /DNDEBUG /MD /EHsc
//
// Debug::GetFrameEntry, retail 0x0003A1B0 (91 bytes), and the out-of-line
// Debug::LookupFrame, retail 0x00038330 (50 bytes).
// Ported from the Open-BFME-1 conversion
// (Libraries/Source/WWVegas/WWDebug/Debug_GetFrameEntry_Thunk.cpp), which
// itself tracks the Zero Hour debug_debug.h layout: a 10007-entry hash table
// at +0x18 holding FrameHashEntry chains (next at +0, frame address at +4,
// status at +0x18). A miss calls AddFrameEntry, then UpdateFrameStatus runs
// when the entry is still Unknown. GetFrameEntry inlines the lookup, which
// is defined first in this TU.
// Dedicated TU so Debug_LogBegin_0088B8F0.cpp keeps its matched LogBegin:
// defining this beside that caller would let MSVC see the callee and change
// the caller's register save set (docs/matching.md pattern five).

#include "../../../../GameEngine/Source/Common/debug.h"

// ?LookupFrame@Debug@@AAEPAUFrameHashEntry@1@I@Z
inline Debug::FrameHashEntry *Debug::LookupFrame(unsigned int address)
{
	for (FrameHashEntry *entry = frameHash[address % FRAME_HASH_SIZE]; entry;
		entry = entry->next)
	{
		if (entry->frameAddr == address)
			return entry;
	}
	return 0;
}

// ?GetFrameEntry@Debug@@AAEPAUFrameHashEntry@1@IIPBDH@Z
Debug::FrameHashEntry *Debug::GetFrameEntry(unsigned int address, unsigned int type,
	const char *fileOrGroup, int line)
{
	FrameHashEntry *entry = LookupFrame(address);
	if (!entry)
		entry = AddFrameEntry(address, type, fileOrGroup, line);
	if (entry->status == Unknown)
		UpdateFrameStatus(*entry);
	return entry;
}
