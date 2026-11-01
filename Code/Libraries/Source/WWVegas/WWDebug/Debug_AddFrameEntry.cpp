// cl: /DNDEBUG /MD /EHsc /Oy-
//
// Debug::AddFrameEntry, retail 0x00038FF0 (223 bytes).
// Ported from Open-BFME-1 WWDebug/debug_debug.cpp AddFrameEntry with two
// BFME2 adaptations attested by retail bytes:
// - AddLogGroup is virtual at vtable slot 0xB4 (45), so it is declared
//   virtual here after 45 placeholder slots to reproduce the indirect call.
// - The non-log filename branch folds both '\\' and '/' via an inline byte
//   loop (no strrchr call), matching retail's separator scan.
// Dedicated TU so the GetFrameEntry TU keeps its matched bodies.

extern void *DebugAllocMemory(unsigned int size);


#include "../../../../GameEngine/Source/Common/debug.h"

// ?AddFrameEntry@Debug@@AAEPAUFrameHashEntry@1@IIPBDH@Z
Debug::FrameHashEntry *Debug::AddFrameEntry(unsigned int addr, unsigned int type,
	const char *fileOrGroup, int line)
{
	if (!numAvailableFrameHash)
	{
		numAvailableFrameHash = FRAME_HASH_ALLOC_COUNT;
		nextUnusedFrameHash = (FrameHashEntry *)DebugAllocMemory(
			numAvailableFrameHash * sizeof(FrameHashEntry));
	}
	FrameHashEntry *entry = nextUnusedFrameHash++;
	--numAvailableFrameHash;

	entry->next = frameHash[addr % FRAME_HASH_SIZE];
	entry->frameAddr = addr;
	entry->frameType = type;
	entry->line = line;
	entry->status = Unknown;
	entry->hits = 0;

	if (type & FrameTypeLog)
	{
		entry->fileOrGroup = AddLogGroup(fileOrGroup, 0);
	}
	else if (fileOrGroup)
	{
		const char *lastSeparator = fileOrGroup;
		const char *cursor = fileOrGroup;
		char current = *cursor;
		if (current)
		{
			for (;;)
			{
				if (current == '\\' || current == '/')
					lastSeparator = cursor + 1;
				current = *++cursor;
				if (!current)
					break;
			}
		}
		entry->fileOrGroup = lastSeparator;
	}
	else
	{
		entry->fileOrGroup = 0;
	}

	frameHash[addr % FRAME_HASH_SIZE] = entry;
	return entry;
}
