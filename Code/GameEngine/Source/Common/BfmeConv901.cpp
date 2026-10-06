// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
//
// ??0BfmeThingJC@@QAE@PAX@Z
// retail 0x002DB882, 33 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngine/Source/Common/BfmeConv901.cpp. Recompiled /Os the
// donor body is byte-identical to retail once relocations are masked (unique
// hit on unclaimed .text). Only the placed body is defined here; the donor's
// other definitions are omitted.
//
// The base class is named for retail 0x001320D0, the body this constructor's
// base-initialiser call lands on: the donor declares that ctor but never
// defines it, so it has no donor name to carry and is pinned address-derived
// (ghidra FUN_005320d0, 89 bytes, unrowed). The constructor body is otherwise
// unchanged from the donor; the base layout at +0x30 and +0x38 is the donor's.
class Rva001320D0
{
public:
	Rva001320D0(void *a);
	virtual ~Rva001320D0();
	char m_bfmePad[0x2c];
	int m_bfme30;
	char m_bfmePad2[4];
	int m_bfme38;
};

class BfmeThingJC : public Rva001320D0
{
public:
	BfmeThingJC(void *a);
	virtual ~BfmeThingJC();
};

BfmeThingJC::BfmeThingJC(void *a) : Rva001320D0(a)
{
	m_bfme30 = 1;
	m_bfme38 = 1;
}