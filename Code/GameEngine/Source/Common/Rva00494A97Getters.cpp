// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
//
// ?rva00589414@Rva00494A97@@UBE?AVAsciiString@@XZ and ?rva00589560@Rva00494A97@@UBE?AVRva002390CB@@XZ @0x00589414 38B.
// Target evidence: the only reference to this body is slot 5 of the
// vtable 0x00C4E900 that the matched Rva00494A97 dtor 0x00494A97 installs at +0x24, the
// +0x24 interface base of the class; the slot's name is not established,
// hence the address name. cl 7.1 compiles an override of a non-primary base's
// virtual with the base subobject's this and folds the adjustment into the
// member accesses, which is why retail reads the module data pointer (+4) as
// [ecx-0x20]. Slot 5 (38B) returns by value the AsciiString at +0x10 of the final override (rowed Overridable::friend_getFinalOverride 0x00288609) of the pointer at +8 of the module data; slot 16 (0x00589560, 30B) returns by value the Rva002390CB at +0x0C of the module data.
#include "ascii_string.h"
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

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
	unsigned char m_pad00[0x10];
	AsciiString m_10;
};
struct Rva00494A97ModuleData
{
	unsigned char m_pad00[8];
	const Overridable *m_08;
	Rva002390CB m_0C;
};
struct B00 { virtual void f00(); const Rva00494A97ModuleData *m_moduleData; Object *m_object; };
struct B0C { virtual void f0C(); };
struct B10 { virtual void f10(); unsigned char m_pad[12]; };
struct B20 { virtual void f20(); };
class Iface24
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual AsciiString rva00589414() const = 0;
	virtual void t00();
	virtual void t01();
	virtual void t02();
	virtual void t03();
	virtual void t04();
	virtual void t05();
	virtual void t06();
	virtual void t07();
	virtual void t08();
	virtual void t09();
	virtual Rva002390CB rva00589560() const = 0;
};
class Rva00494A97 : public B00, public B0C, public B10, public B20, public Iface24
{
public:
	virtual AsciiString rva00589414() const;
	virtual Rva002390CB rva00589560() const;
};
AsciiString Rva00494A97::rva00589414() const
{
	return m_moduleData->m_08->friend_getFinalOverride()->m_10;
}
Rva002390CB Rva00494A97::rva00589560() const
{
	return m_moduleData->m_0C;
}
