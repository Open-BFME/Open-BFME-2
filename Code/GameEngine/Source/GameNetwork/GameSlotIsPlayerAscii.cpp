// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?isPlayer@GameSlot@@QBE_NVAsciiString@@@Z @0x003FFEF5 (109B):
// GameSlot::isPlayer, AsciiString by-value overload. BFME1
// GameSlotIsPlayerAsciiThunk.cpp donor
// (reference/open-bfme-1/.../GameNetwork/GameSlotIsPlayerAsciiThunk.cpp):
// state==SLOT_PLAYER plus translate then name compareNoCase, ret 4. BFME2
// adaptations proven by the retail bytes:
// - SLOT_PLAYER is 6 (retail cmp [ecx+4],6; ZH numbers it 5).
// - m_name sits at +0x30 (retail lea ecx,[esi+0x30]; BFME1 places it at +0x28).
// Callees already settled: UnicodeString::translate is rowed at 0x6CB6A0,
// StringBase<G>::compareNoCase is rowed at 0x6AA4,
// StringBase<G>::releaseBuffer is rowed at 0x36E70,
// StringBase<D>::releaseBuffer is rowed at 0x36410. No new pins.

typedef int Int;
typedef bool Bool;

enum
{
	SLOT_OPEN,
	SLOT_CLOSED,
	SLOT_EASY_AI,
	SLOT_MED_AI,
	SLOT_BRUTAL_AI,
	SLOT_AI_5,
	SLOT_PLAYER
};

#include "ascii_string.h"
#include "unicode_string.h"



class GameSlot
{
public:
	virtual void reset(void) = 0;
	Bool isPlayer(AsciiString userName) const;

protected:
	Int m_state;
	unsigned char m_gap08[0x30 - 0x08];
	UnicodeString m_name;
};

Bool GameSlot::isPlayer(AsciiString userName) const
{
	UnicodeString uName;
	uName.translate(userName);
	Bool result;
	if (m_state == SLOT_PLAYER && m_name.compareNoCase(uName) == 0)
		result = true;
	else
		result = false;
	return result;
}
