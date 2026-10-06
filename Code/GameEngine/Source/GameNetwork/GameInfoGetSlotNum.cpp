// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?getSlotNum@GameInfo@@QBEHVAsciiString@@@Z @0x40009A (140B):
// GameInfo::getSlotNum, AsciiString by-value overload. BFME1
// GameInfo_getSlotNum_Thunk.cpp donor
// (reference/open-bfme-1/.../GameNetwork/GameInfo_getSlotNum_Thunk.cpp):
// inGame gate plus per-slot isPlayer scan over the translated Unicode name
// with the found index returned directly, ret 4. BFME2 adaptations proven
// by the retail bytes:
// - the inGame flag sits at +0x10 (retail cmp byte ptr [ebx+0x10],0).
// - the Unicode temp carries the non-trivial StringBase dtor (retail tracks
//   EH state 1 across translate) while the per-iteration by-value temp is
//   callee-released by isPlayer itself so the loop stays frameless-clean.
//   The tail release reaches the pinned releaseBuffer through the inlined
//   base dtor (GameSlotIsPlayer.cpp ownership precedent).
// Callees already settled: getConstSlot is rowed at 0x3FF2BE, isPlayer is
// rowed at 0x3FFF62, UnicodeString::translate is rowed at 0x6CB6A0,
// StringBase<G> copy-ctor and releaseBuffer are pinned at 0x37050/0x36E70,
// AsciiString::~AsciiString is pinned at 0x36410. No new pins.

typedef int Int;
typedef bool Bool;

enum
{
	MAX_SLOTS = 8
};

#include "ascii_string.h"


#include "unicode_string.h"

class GameSlot
{
public:
	Bool isPlayer(UnicodeString userName) const;
};

class GameInfo
{
public:
	const GameSlot *getConstSlot(Int slotNum) const;
	Int getSlotNum(AsciiString userName) const;

private:
	unsigned char m_pad[0x10];
	Bool m_inGame;
};

// ?getSlotNum@GameInfo@@QBEHVAsciiString@@@Z
Int GameInfo::getSlotNum(AsciiString userName) const
{
	if (!m_inGame)
		return -1;

	UnicodeString uName;
	uName.translate(userName);
	for (Int i = 0; i < MAX_SLOTS; ++i)
	{
		const GameSlot *slot = getConstSlot(i);
		if (slot->isPlayer(uName))
			return i;
	}
	return -1;
}
