// cl: /DNDEBUG /MD /EHs-c- /Oy-
//
// Debug::AddPatternEntry, retail 0x000393E0 (147 bytes).
// Ported from Open-BFME-1 WWDebug/Debug_AddPatternEntry_Thunk.cpp: allocate
// a 16-byte PatternListEntry, fold the pattern via _strlwr for
// case-insensitive matching, append to the (+0x9E00, +0x9E04) list.
// strlen/strcpy are intrinsics (byte loops, no calls); _strlwr is the only
// import call. Dedicated TU to keep its frame codegen isolated.

#include <string.h>

extern void *DebugAllocMemory(unsigned int size);


#include "../../../../GameEngine/Source/Common/debug.h"

// ?AddPatternEntry@Debug@@AAEXI_NPBD@Z
void Debug::AddPatternEntry(unsigned int types, bool isActive, const char *pattern)
{
	PatternListEntry *entry = (PatternListEntry *)DebugAllocMemory(sizeof(PatternListEntry));
	entry->next = 0;
	entry->frameTypes = types;
	entry->isActive = isActive;
	entry->pattern = (char *)DebugAllocMemory(strlen(pattern) + 1);
	strcpy(entry->pattern, pattern);
	_strlwr(entry->pattern);

	if (lastPatternEntry)
		lastPatternEntry->next = entry;
	else
		firstPatternEntry = entry;
	lastPatternEntry = entry;
}
