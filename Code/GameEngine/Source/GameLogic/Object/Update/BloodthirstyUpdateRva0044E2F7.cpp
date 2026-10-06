// cl: /DNDEBUG /MD
//
// ?rva0044E2F7@BloodthirstyUpdate@@UBE?AVRva002390CB@@XZ @0x0044E2F7 30B.
// Target evidence: the only reference to this body is slot 9 of the
// vtable 0x00C3EFC4 that the matched BloodthirstyUpdate dtor 0x0044DFE0 installs at +0x20, the
// +0x20 interface base of the class; the slot's name is not established,
// hence the address name. cl 7.1 compiles an override of a non-primary base's
// virtual with the base subobject's this and folds the adjustment into the
// member accesses, which is why retail reads the module data pointer (+4) as
// [ecx-0x1C]. Returns by value (hidden pointer, Rva002390CB copy ctor 0x002390CB) the Rva002390CB at +0x10 of the module data; the +0x0C/+0x10 bases are the two UpdateModule interfaces of the BloodthirstyUpdate dtor TU model.
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
struct BloodthirstyUpdateModuleData
{
	unsigned char m_pad00[0x10];
	Rva002390CB m_10;
};
struct B00 { virtual void f00(); const BloodthirstyUpdateModuleData *m_moduleData; Object *m_object; };
struct B0C { virtual void f0C(); };
struct B10 { virtual void f10(); unsigned char m_pad[12]; };
class Iface20
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
	virtual Rva002390CB rva0044E2F7() const = 0;
};
class BloodthirstyUpdate : public B00, public B0C, public B10, public Iface20
{
public:
	virtual Rva002390CB rva0044E2F7() const;
};
Rva002390CB BloodthirstyUpdate::rva0044E2F7() const
{
	return m_moduleData->m_10;
}
