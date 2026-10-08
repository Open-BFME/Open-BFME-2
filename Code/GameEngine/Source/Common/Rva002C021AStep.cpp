// cl: /MD
// ?rva002C021A@Rva002C021A@@QAEXXZ @0x002C021A 64B.
// Pause-gated step: returns while the TheGameLogic global reports paused or
// the byte at +0x18 is clear; otherwise runs the unrowed thiscall helpers
// 0x002BFF9F and 0x002BF77B, calls virtual slot 10 of the singleton host
// 0x009FE1C8 (VA 0x00DFE1C8), and tail-jumps to the unrowed thiscall
// 0x002BEBE3 when the byte at +0x78 is set. The three callees are pinned by
// their REL32 sites. Evidence: target only; names are address-derived.
#include "GameLogicObjectLookupView.h"

extern void *g_00DFE78C;

class Rva00DFE1C8Host
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(void);
};

extern Rva00DFE1C8Host *g_00DFE1C8;

class Rva002C021A
{
public:
	void rva002C021A();
	void rva002BFF9F();
	void rva002BF77B();
	void rva002BEBE3();

private:
	char m_pad00[0x18];
	unsigned char m_18;
	char m_pad19[0x78 - 0x19];
	unsigned char m_78;
};

void Rva002C021A::rva002C021A()
{
	if (((GameLogic *)g_00DFE78C)->isGamePaused())
		return;
	if (!m_18)
		return;
	rva002BFF9F();
	rva002BF77B();
	g_00DFE1C8->slot28();
	if (m_78)
		rva002BEBE3();
}
