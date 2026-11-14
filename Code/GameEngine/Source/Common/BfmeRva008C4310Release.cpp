// Release path: drop from a tracker, clear the holder slot, then tail-release.
// Ported from Open-BFME-1 Code/GameEngine/Source/Common/BfmeRva008C4310Release.cpp
// (BFME1 0x00896FF0). Only the placed tracker-side drop is defined here; the
// donor's object-side drop stays declared-only so the unmatched-definition
// gate passes. Retail 0x006D2580 (52B) walks the tracker list and erases the
// node whose payload+8 holder matches, via the single pinned erase call.

// (Kept for layout honesty; defined elsewhere.)
class BfmeObj4310;

class BfmeNodeVMU
{
public:
	void *m_bfmePayload;
	BfmeNodeVMU *m_bfmeNext;
};

#include "../../Include/Common/BfmeListVMU.h"

class BfmeTracker4310 : public BfmeListVMU
{
public:
	__declspec(noinline) void bfmeDrop(BfmeObj4310 *obj);
};

// ?bfmeDrop@BfmeTracker4310@@QAEXPAVBfmeObj4310@@@Z, retail 0x006D2580 (52B).
void BfmeTracker4310::bfmeDrop(BfmeObj4310 *obj)
{
	BfmeNodeVMU *node = head;
	while (node != 0)
	{
		if (*(BfmeObj4310 **)((char *)node->m_bfmePayload + 8) == obj)
		{
			BfmeNodeVMU *erase = node;
			bfmeEraseVMU(&erase);
			return;
		}
		node = node->m_bfmeNext;
	}
}
