// cl: /DNDEBUG /MD /EHsc
// ?isPlayer@GameSlot@@QBE_NVUnicodeString@@@Z @0x3FFF62 (45B):
// GameSlot::isPlayer, UnicodeString by-value overload. BFME1
// GameSlotIsPlayerUnicodeThunk.cpp donor
// (reference/open-bfme-1/.../GameNetwork/GameSlotIsPlayerUnicodeThunk.cpp):
// state==SLOT_PLAYER plus name compareNoCase, explicit releaseBuffer on the
// by-value name, ret 4. BFME2 adaptations proven by the retail bytes:
// - SLOT_PLAYER is 6 (retail cmp [ecx+4],6; ZH numbers it 5).
// - m_name sits at +0x30 (retail add ecx,0x30; ZH places it at +0x28).
// Callees already settled: StringBase<G>::compareNoCase is rowed at 0x6AA4,
// StringBase<G>::releaseBuffer is pinned at 0x36E70. No new pins.
// The by-value name is released by its callee-side destructor (the shared
// header's inline ~UnicodeString -> releaseBuffer).

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

#include "../../../../reference/shims/bfme2_ascii/unicode_string.h"

class GameSlot
{
public:
	virtual void reset(void) = 0;
	Bool isPlayer(UnicodeString userName) const;

protected:
	Int m_state;
	unsigned char m_gap08[0x30 - 0x08];
	UnicodeString m_name;
};

// ?isPlayer@GameSlot@@QBE_NVUnicodeString@@@Z
Bool GameSlot::isPlayer(UnicodeString userName) const
{
	Bool result;
	if (m_state == SLOT_PLAYER && m_name.compareNoCase(userName) == 0)
		result = true;
	else
		result = false;

	return result;
}

// ?isPlayer@Rva004481A7@@QBE_NVUnicodeString@@@Z @0x004481A7 (45B):
// Same GameSlot layout (m_state +4 == 6 is SLOT_PLAYER, m_name +0x30);
// retail calls compareNoCase on the by-value param with m_name as the
// argument (add ecx,0x30 then push, lea ecx,[esp+0xc]), where the 0x3FFF62
// twin calls it on m_name. Frameless 45B with the by-value releaseBuffer, ret 4.
class Rva004481A7
{
public:
	virtual void reset(void) = 0;
	Bool isPlayer(UnicodeString userName) const;

protected:
	Int m_state;
	unsigned char m_gap08[0x30 - 0x08];
	UnicodeString m_name;
};
