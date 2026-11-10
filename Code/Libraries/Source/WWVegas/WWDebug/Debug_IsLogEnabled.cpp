// cl: /DNDEBUG /MD /EHsc
//
// Debug::isLogEnabled, retail 0x0003B5D0 (109 bytes).
// Ported from Open-BFME-1 WWDebug/Debug_isLogEnabled.cpp: hash lookup with
// miss-allocate via AddFrameEntry(type 4, address as name), lazy
// UpdateFrameStatus when Unknown, true for statuses 2 or 3.
// Dedicated TU with frame pointer (retail has ebp frame) so the matched
// GetFrameEntry TU keeps its frameless codegen.

#include "../../../../GameEngine/Source/Common/debug.h"

// The canonical FrameHashEntry matches the pinned provider's layout; both are
// thiscall void updates with one reference argument at retail 0x00039A60.
#pragma comment(linker, "/alternatename:?UpdateFrameStatus@Debug@@AAEXAAUFrameHashEntry@1@@Z=?UpdateFrameStatus@Rva0088A7E0Debug@@QAEXAAURva0088A7E0FrameHashEntry@@@Z")

// LookupFrame is frameless at retail RVA 0x00038330.

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

// The matched caller retains its frame pointer.
#pragma optimize("y", off)

// ?isLogEnabled@Debug@@UAE_NI@Z
bool Debug::isLogEnabled(unsigned int address)
{
	FrameHashEntry *entry = LookupFrame(address);
	if (!entry)
		entry = AddFrameEntry(address, FrameTypeLog, (const char *)address, 0);
	if (entry->status == Unknown)
		UpdateFrameStatus(*entry);
	return entry->status == 2 || entry->status == 3;
}
