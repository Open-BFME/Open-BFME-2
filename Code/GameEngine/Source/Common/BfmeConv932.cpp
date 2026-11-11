class BfmeSub932C
{
public:
	unsigned char bfmeQuery932C();
};

class BfmeThing932C
{
public:
	int bfmeGo932C();
	char m_bfmePad[0x24];
	BfmeSub932C *m_bfmeSub;
};

int BfmeThing932C::bfmeGo932C()
{
	BfmeSub932C *s = m_bfmeSub;
	if (s)
		return s->bfmeQuery932C();
	return 0;
}

#include "../../Include/Common/BfmeThing932E.h"

void BfmeThing932E::bfmeGo932E()
{
	if (!bfmeTest932E())
		bfmeTail932E();
}

struct BfmeSlotJA;

class BfmeHookJA
{
public:
	BfmeSlotJA *bfmeCallJA();
};

struct BfmeSlotJA
{
	char m_bfmePad[4];
	BfmeHookJA *m_nextOverride;
};

class ThingTemplate;

class MapObject
{
public:
	const ThingTemplate *getThingTemplate() const;
	char m_bfmePad[0x18];
	BfmeSlotJA *m_bfmeSlot;
};

// ?getThingTemplate@MapObject@@QBEPBVThingTemplate@@XZ, retail 0x0030D833 (22B).
//
// The hook call is a tail jmp (same shape as the donor); it resolves
// through the ledger pin at 0x001E35DF, whose +4-chain-walker bytes are
// neutrally rowed as a dup_ span.
const ThingTemplate *MapObject::getThingTemplate() const
{
	BfmeSlotJA *s = m_bfmeSlot;
	if (s) {
		BfmeHookJA *h = s->m_nextOverride;
		if (h)
			return (const ThingTemplate *)h->bfmeCallJA();
		return (const ThingTemplate *)s;
	}
	return 0;
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below. Bind the donor spelling to that owner so one
// address keeps one definition and the unit links.
//   0x00347460 reads ?update@AIInternalMoveToState@@UAE?AW4StateReturnType@@XZ
#pragma comment(linker, "/alternatename:?bfmeTail932E@BfmeThing932E@@QAEXXZ=?update@AIInternalMoveToState@@UAE?AW4StateReturnType@@XZ")
//   0x0034612C reads ?internalUpdate@AICombineState@@QAE?AW4StateReturnType@@XZ
#pragma comment(linker, "/alternatename:?bfmeTest932E@BfmeThing932E@@QAEHXZ=?internalUpdate@AICombineState@@QAE?AW4StateReturnType@@XZ")
