// cl: /DNDEBUG /MD /EHsc
//
// ?rva0027248A@Drawable@@QAEXHH@Z, retail 0x0027248A, 58 bytes.
// Guarded broadcaster: when the +0xFC pointer is set, walk the +0x14C draw
// modules via slot 0xA8 and forward two int args to slot 0x7C targets.
// Evidence: same +0x14C/slot-0xA8 walk as Drawable siblings in neighbour
// Drawable_rva002724FD.cpp (frameless so /Oy- dropped); +0xFC guard as in
// rva00272414; ret 8 two args; unblocks 0x004083FF; caller 0x0040869B.

class BfmeObjectDrawForRva27248A
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
	virtual void slot78() = 0;
	virtual void rva0027248ATarget(int a, int b) = 0;
};

class BfmeDrawModuleForRva27248A
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
	virtual BfmeObjectDrawForRva27248A *getObjectDrawInterface() = 0;
};

class Drawable
{
public:
	void rva0027248A(int a, int b);
};

void Drawable::rva0027248A(int a, int b)
{
	if (*(void **)((unsigned char *)this + 0xFC) == 0)
		return;
	BfmeDrawModuleForRva27248A **modules =
		*reinterpret_cast<BfmeDrawModuleForRva27248A ***>((unsigned char *)this + 0x14C);
	for (BfmeDrawModuleForRva27248A **dm = modules; *dm; ++dm) {
		BfmeObjectDrawForRva27248A *di = (*dm)->getObjectDrawInterface();
		if (di)
			di->rva0027248ATarget(a, b);
	}
}
