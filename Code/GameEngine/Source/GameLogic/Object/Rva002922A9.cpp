// cl: /O1 /MD
// Retail 0x002922A9, 48 bytes. Fire a special power through module 0x8B:
// the slot-0x18 virtual is a no-arg call whose result feeds 0x28E0F9 as its
// first arg, so the three earlier pushes double as 0x28E0F9's (b,c,d). View
// mirrors the Rva003BCD1BDo sibling (Object::findSpecialPowerModuleInterface,
// SpecialPowerModuleInterface vtable); 0x28E0F9 pinned under its banked
// Rva0028E0F9Host identity (ret-16 4-arg thiscall verified from its tail).
class SpecialPowerModuleInterface
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual int s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
};
enum SpecialPowerType
{
	SPECIAL_INVALID = 0
};
class Object
{
public:
	SpecialPowerModuleInterface *findSpecialPowerModuleInterface(SpecialPowerType type) const;
};
class Rva0028E0F9Host : public Object
{
public:
	void rva0028E0F9(int a, int b, int c, bool d);
};
class Rva002922A9Host : public Rva0028E0F9Host
{
public:
	void rva002922A9(void *arg);
};
// ?rva002922A9@Rva002922A9Host@@QAEXPAX@Z
void Rva002922A9Host::rva002922A9(void *arg)
{
	SpecialPowerModuleInterface *sp = findSpecialPowerModuleInterface((SpecialPowerType)0x8B);
	if (sp == 0)
		return;
	rva0028E0F9(sp->s06(), (int)((char *)arg + 0x38), 2, false);
}
