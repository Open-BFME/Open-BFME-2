// cl: /O1 /MD
// ?Rva00489256Do@@YAXPAVObject@@@Z @0x00489256 95B ret 0
// Deselect drawable via TheInGameUI slot 0x10C then check rva004884B7 and
// set status mask (0 0x3c 3 0x4f 0x63) via Object::rva0028CDEB(true) then
// rva0028BAC0 when byte at +0x454 is set. Evidence: InGameUI slot 67 is
// deselectDrawable and Rva00346BC0 ctor IIIII and Object::rva0028CDEB and
// pin-only rva0028BAC0 and caller 0x004892E1. Static private esi convention
// with same-TU caller per precedent Rva003504E0.cpp.
class Drawable;
class Thing
{
public:
	Drawable *getDrawable() const;
};
class Rva00346BC0
{
public:
	Rva00346BC0(unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4, unsigned int a5);
private:
	unsigned int m_bits[4];
};
class Object
{
public:
	void rva0028CDEB(const Rva00346BC0 &mask, bool set);
};
class Rva0028BAC0
{
public:
	void rva0028BAC0();
};
bool __cdecl rva004884B7(Object *obj);
class InGameUISlots
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
	virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51();
	virtual void s52(); virtual void s53(); virtual void s54(); virtual void s55();
	virtual void s56(); virtual void s57(); virtual void s58(); virtual void s59();
	virtual void s60(); virtual void s61(); virtual void s62(); virtual void s63();
	virtual void s64(); virtual void s65(); virtual void s66();
};
class InGameUI : public InGameUISlots
{
public:
	virtual void deselectDrawable(Drawable *draw);
};
extern InGameUI *TheInGameUI;
static __declspec(noinline) void Rva00489256Do(Object *obj)
{
	TheInGameUI->deselectDrawable(reinterpret_cast<Thing *>(obj)->getDrawable());
	if (rva004884B7(obj))
		return;
	Rva00346BC0 mask(0, 0x3c, 3, 0x4f, 0x63);
	obj->rva0028CDEB(mask, true);
	if (*(unsigned char *)((char *)obj + 0x454) != 0)
		reinterpret_cast<Rva0028BAC0 *>(obj)->rva0028BAC0();
}
void Rva00489256DoCaller(Object *obj)
{
	Rva00489256Do(obj);
}
