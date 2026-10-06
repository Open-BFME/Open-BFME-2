// cl: /DNDEBUG /MD
// ?rva00270FAC@Drawable@@QAEX_N@Z @0x00270FAC 66B
// Drawable broadcast over draw modules at +0x14C via slot 0xA8 to slot 0x54 with int from +0x454 gated by flag at +0x3AA.
// Evidence: callers 0x003C36C0 0x003C36FE call Thing::getDrawable (ICF twin at 0x005508E2) then this; same +0x14C/0xA8 walk as Drawable_rva002724FD 0x002724FD; Drawable+0xFC is object (InGameUI_selectMatchingAcrossMap); honest Drawable method name.
class BfmeObjectDrawFor270FAC
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4C() = 0;
	virtual void slot50() = 0;
	virtual void target(int a) = 0;
};

class BfmeDrawModuleFor270FAC
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4C() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58() = 0;
	virtual void slot5C() = 0;
	virtual void slot60() = 0;
	virtual void slot64() = 0;
	virtual void slot68() = 0;
	virtual void slot6C() = 0;
	virtual void slot70() = 0;
	virtual void slot74() = 0;
	virtual void slot78() = 0;
	virtual void slot7C() = 0;
	virtual void slot80() = 0;
	virtual void slot84() = 0;
	virtual void slot88() = 0;
	virtual void slot8C() = 0;
	virtual void slot90() = 0;
	virtual void slot94() = 0;
	virtual void slot98() = 0;
	virtual void slot9C() = 0;
	virtual void slotA0() = 0;
	virtual void slotA4() = 0;
	virtual BfmeObjectDrawFor270FAC *getObjectDrawInterface() = 0;
};

class Drawable
{
public:
	void rva00270FAC(bool b);
};

void Drawable::rva00270FAC(bool b)
{
	*(bool *)((unsigned char *)this + 0x3aa) = b;
	int val = 0;
	if (b == 1)
		val = *(int *)((unsigned char *)this + 0x454);
	BfmeDrawModuleFor270FAC **modules = *reinterpret_cast<BfmeDrawModuleFor270FAC ***>((unsigned char *)this + 0x14c);
	for (BfmeDrawModuleFor270FAC **dm = modules; *dm; ++dm) {
		BfmeObjectDrawFor270FAC *di = (*dm)->getObjectDrawInterface();
		if (di)
			di->target(val);
	}
}
