// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva0027656F@Drawable@@QAEXHVAsciiString@@@Z, retail 0x0027656F, 101 bytes.
// Drawable broadcaster over draw modules at this+0x14C via slot 0xA8
// getObjectDrawInterface, forwarding (int, AsciiString by value) to
// slot 0x44 targets. Evidence: same +0x14C/slot-0xA8 walk as landed
// Drawable_rva002724FD 0x002724FD and Drawable_rva00278689 0x00278689;
// per-iteration AsciiString copy via pinned 0x000365F0 (inline forwarder
// order per shape_levers by-value string row) and by-value param teardown
// via pin 0x00036410.
template <typename T>
struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

#include "ascii_string.h"


class BfmeObjectDrawFor27656F
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0;
	virtual void slot08() = 0; virtual void slot0C() = 0;
	virtual void slot10() = 0; virtual void slot14() = 0;
	virtual void slot18() = 0; virtual void slot1C() = 0;
	virtual void slot20() = 0; virtual void slot24() = 0;
	virtual void slot28() = 0; virtual void slot2C() = 0;
	virtual void slot30() = 0; virtual void slot34() = 0;
	virtual void slot38() = 0; virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void rva27656FTarget(int a1, AsciiString a2) = 0;
};

class BfmeDrawModuleFor27656F
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0;
	virtual void slot08() = 0; virtual void slot0C() = 0;
	virtual void slot10() = 0; virtual void slot14() = 0;
	virtual void slot18() = 0; virtual void slot1C() = 0;
	virtual void slot20() = 0; virtual void slot24() = 0;
	virtual void slot28() = 0; virtual void slot2C() = 0;
	virtual void slot30() = 0; virtual void slot34() = 0;
	virtual void slot38() = 0; virtual void slot3C() = 0;
	virtual void slot40() = 0; virtual void slot44() = 0;
	virtual void slot48() = 0; virtual void slot4C() = 0;
	virtual void slot50() = 0; virtual void slot54() = 0;
	virtual void slot58() = 0; virtual void slot5C() = 0;
	virtual void slot60() = 0; virtual void slot64() = 0;
	virtual void slot68() = 0; virtual void slot6C() = 0;
	virtual void slot70() = 0; virtual void slot74() = 0;
	virtual void slot78() = 0; virtual void slot7C() = 0;
	virtual void slot80() = 0; virtual void slot84() = 0;
	virtual void slot88() = 0; virtual void slot8C() = 0;
	virtual void slot90() = 0; virtual void slot94() = 0;
	virtual void slot98() = 0; virtual void slot9C() = 0;
	virtual void slotA0() = 0; virtual void slotA4() = 0;
	virtual BfmeObjectDrawFor27656F *getObjectDrawInterface() = 0;
};

class Drawable
{
public:
	void rva0027656F(int a1, AsciiString a2);
};

void Drawable::rva0027656F(int a1, AsciiString a2)
{
	BfmeDrawModuleFor27656F **modules =
		*reinterpret_cast<BfmeDrawModuleFor27656F ***>((unsigned char *)this + 0x14C);
	for (BfmeDrawModuleFor27656F **dm = modules; *dm; ++dm) {
		BfmeObjectDrawFor27656F *di = (*dm)->getObjectDrawInterface();
		if (di) {
			di->rva27656FTarget(a1, a2);
		}
	}
}
