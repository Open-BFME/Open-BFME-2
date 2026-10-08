// cl: /DNDEBUG /MD /EHsc
//
// InGameUI slots 99-100: monotonic max-setter plus clearer over the
// unsigned field at +0x7EC. Slot evidence from the InGameUI vtable at
// 0x7BE810 (slots 88-89 are the landed selectMatching pair, so the table
// is proven): slot 99 points at 0x0029B04D, slot 100 at 0x0029B060, and
// the clearer sits immediately after the setter with no other references.
// Both are leaves (no calls, no pins). The member is unsigned (retail
// compares with jbe, not jle) and the pad is 4 short of the offset for
// the vtable pointer. Semantic names are unproven so both ride
// address-derived InGameUI-scoped names; opaque behavior.
//
// Slot 111 of vftable 0x007FD410 (0x0029B068) is ZH's areTooltipsDisabled,
// the slot after ZH's disableTooltipsUntil/clearTooltipsDisabled pair, which
// fits the two bodies above. BFME 2 first reports tooltips disabled while
// TheGlobalData's byte +0xDD0 is clear and enabled while TheLivingWorldLogic's
// selection guard 0x0004253A holds; then ZH's frame test against +0x7EC. The
// +0xDD0 field name is descriptive.

#include "../Common/GameLogicObjectLookupView.h"

class GlobalData
{
public:
	char m_opaque000[0xDD0];
	bool m_unknownDD0;	// +0xDD0
};
extern GlobalData *TheWritableGlobalData;
#define TheGlobalData ((const GlobalData *)TheWritableGlobalData)

extern GameLogic *TheGameLogic;

// BFME2 selection-state guard: true only if bytes +0xB4/+0xB5 are both set.
class BfmeSelectionState
{
public:
	bool isSelectionLocked() const;
};
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

class InGameUI
{
	char m_pad[0x7EC - 4];
	unsigned int m_7EC;
public:
	virtual void setRva0029B04D(int value);
	virtual void clearRva0029B060();
	virtual bool areTooltipsDisabled() const;
};

// ?setRva0029B04D@InGameUI@@UAEXH@Z
void InGameUI::setRva0029B04D(int value)
{
	if (value > m_7EC)
		m_7EC = value;
}

// ?clearRva0029B060@InGameUI@@UAEXXZ
void InGameUI::clearRva0029B060()
{
	m_7EC = 0;
}

// ?areTooltipsDisabled@InGameUI@@UBE_NXZ
bool InGameUI::areTooltipsDisabled() const
{
	if (!TheGlobalData->m_unknownDD0)
		return true;
	BfmeSelectionState *state = *(BfmeSelectionState **)&TheLivingWorldLogic;
	return !(state && state->isSelectionLocked()) && TheGameLogic->getFrame() < m_7EC;
}
