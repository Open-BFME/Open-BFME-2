// cl: /MD
// ?rva004E624D@Rva004E624D@@QAEXXZ @ 0x004E624D 38B unlock: guarded pair of virtual calls through +0x1c slot 8 then DisplayStringManager slot 0x3c with +0x10. Manager layout per Rva004E5821Method (new at 0x38 free at 0x3c) global TheDisplayStringManager VA 0xdfead8. Unblocks 0x004E63E2 0x004E630C.
class DisplayString;

#include "../../../Include/GameClient/DisplayStringManager.h"

extern DisplayStringManager *TheDisplayStringManager;

struct Rva004E624DTarget
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
};

struct Rva004E624D
{
	char m_00[16];
	DisplayString *m_10;
	char m_14[8];
	Rva004E624DTarget *m_1c;
	void rva004E624D();
};

void Rva004E624D::rva004E624D()
{
	if (m_1c != 0)
		m_1c->v2();
	DisplayString *displayString = m_10;
	if (displayString != 0)
		TheDisplayStringManager->freeDisplayString(displayString);
}
