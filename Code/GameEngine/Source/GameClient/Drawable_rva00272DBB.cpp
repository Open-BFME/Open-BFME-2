// cl: /DNDEBUG /MD /EHsc
//
// ?rva00272DBB@Drawable@@QAEXPAVObject@@@Z, retail 0x00272DBB, 51 bytes.
// Guarded draw-module walk: when the Object arg is non-null and
// isKindOf(0x45), walk this+0x14C modules calling slot 0xF4.
// Evidence: same +0x14C walk as Drawable siblings 0x00272393/0x002723C0/
// 0x002723ED; rowed ?isKindOf@Object@@QBE_NW4KindOfType@@@Z at 0x0006F039;
// unblocks 0x0027566B; caller at 0x002756F0.

typedef bool Bool;
enum KindOfType;

class Object
{
public:
	Bool isKindOf(KindOfType kind) const;
};

class DrawModuleForRva272DBB
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
	virtual void slotA8() = 0; virtual void slotAC() = 0;
	virtual void slotB0() = 0; virtual void slotB4() = 0;
	virtual void slotB8() = 0; virtual void slotBC() = 0;
	virtual void slotC0() = 0; virtual void slotC4() = 0;
	virtual void slotC8() = 0; virtual void slotCC() = 0;
	virtual void slotD0() = 0; virtual void slotD4() = 0;
	virtual void slotD8() = 0; virtual void slotDC() = 0;
	virtual void slotE0() = 0; virtual void slotE4() = 0;
	virtual void slotE8() = 0; virtual void slotEC() = 0;
	virtual void slotF0() = 0;
	virtual void rva00272DBBTarget() = 0;
};

class Drawable
{
public:
	void rva00272DBB(Object *obj);
};

void Drawable::rva00272DBB(Object *obj)
{
	if (obj == 0)
		return;
	if (!obj->isKindOf((KindOfType)0x45))
		return;
	DrawModuleForRva272DBB **modules =
		*reinterpret_cast<DrawModuleForRva272DBB ***>((unsigned char *)this + 0x14C);
	for (DrawModuleForRva272DBB **p = modules; *p; ++p)
		(*p)->rva00272DBBTarget();
}
