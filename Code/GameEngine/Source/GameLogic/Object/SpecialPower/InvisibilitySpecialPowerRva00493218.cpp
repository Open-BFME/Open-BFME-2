// cl: /DNDEBUG /MD
//
// ?rva00493218@InvisibilitySpecialPower@@UBE?AVRva002390CB@@XZ @0x00493218 30B.
// Target evidence: the only reference to this body is slot 16 of the
// vtable 0x00C5C4B8 that the matched InvisibilitySpecialPower ctor 0x004C23A4 installs at +0x10, the
// +0x10 interface base of the class; the slot's name is not established,
// hence the address name. cl 7.1 compiles an override of a non-primary base's
// virtual with the base subobject's this and folds the adjustment into the
// member accesses, which is why retail reads the module data pointer (+4) as
// [ecx-0xC]. Returns by value (hidden pointer, Rva002390CB copy ctor 0x002390CB) the Rva002390CB at +0x10 of the module data.
class Thing;
class ModuleData;
class Object;
class Rva002390CB
{
public:
	Rva002390CB(const Rva002390CB &other);
	~Rva002390CB();
private:
	void *m_data;
};

struct InvisibilitySpecialPowerModuleData
{
	unsigned char m_pad00[0x10];
	Rva002390CB m_10;
};
struct B00 { virtual void f00(); const InvisibilitySpecialPowerModuleData *m_moduleData; Object *m_object; };
struct B0C { virtual void f0C(); };
class Iface10
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual Rva002390CB rva00493218() const = 0;
};
class InvisibilitySpecialPower : public B00, public B0C, public Iface10
{
public:
	virtual Rva002390CB rva00493218() const;
};
Rva002390CB InvisibilitySpecialPower::rva00493218() const
{
	return m_moduleData->m_10;
}
