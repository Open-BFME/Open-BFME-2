// cl: C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva00067878@BaseHeightMapRenderObjClass@@QAEXXZ, retail 0x00067878, 67 bytes.
// Unlock lane: releases ref-counted holders at +0xCC/+0xD0 (dec ref at +4,
// virtual slot0 if zero, then and-zero) then tail-jumps to rowed
// ?clear@BfmeResetTextureRef@@QAEXXZ at 0x0004D75B for +0xD4.
// Evidence: callers at 0x00069340/0x0006B416 (both unclaimed), rowed callee,
// and-zero plus tail-jmp shape.

struct BfmeResetResource;

struct RefObj00067878
{
	virtual void v0();
	int m_ref;
};

#include "../../../Libraries/Source/WWVegas/WW3D2/BfmeResetTextureRef.h"

class BaseHeightMapRenderObjClass
{
public:
	void rva00067878();
private:
	unsigned char m_pad[0xCC];
	RefObj00067878 *m_a;
	RefObj00067878 *m_b;
	BfmeResetTextureRef m_c;
};

void BaseHeightMapRenderObjClass::rva00067878()
{
	RefObj00067878 *a = m_a;
	if (a)
	{
		if (--a->m_ref == 0)
			a->v0();
		m_a = 0;
	}
	RefObj00067878 *b = m_b;
	if (b)
	{
		if (--b->m_ref == 0)
			b->v0();
		m_b = 0;
	}
	return m_c.clear();
}
