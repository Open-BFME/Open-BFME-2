// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
//
// ?rva004B8851@Rva004B8732@@UBE?AVAsciiString@@XZ @0x004B8851 30B.
// Target evidence: the only reference to this body is slot 0 of the
// vtable 0x00C59120 that the matched Rva004B8732 dtor 0x004B8732 installs at +0x20, the
// +0x20 interface base of the class; the slot's name is not established,
// hence the address name. cl 7.1 compiles an override of a non-primary base's
// virtual with the base subobject's this and folds the adjustment into the
// member accesses, which is why retail reads the module data pointer (+4) as
// [ecx-0x1C]. Returns by value (hidden pointer, StringBase<char> copy ctor 0x000365F0 through the shared AsciiString shim) the AsciiString at +8 of the module data.
#include "ascii_string.h"
class Thing;
class ModuleData;
class Object;
struct Rva004B8732ModuleData
{
	unsigned char m_pad00[8];
	AsciiString m_08;
};
struct B00 { virtual void f00(); const Rva004B8732ModuleData *m_moduleData; Object *m_object; };
struct B0C { virtual void f0C(); };
struct B10 { virtual void f10(); unsigned char m_pad[12]; };
class Iface20
{
public:
	virtual AsciiString rva004B8851() const = 0;
};
class Rva004B8732 : public B00, public B0C, public B10, public Iface20
{
public:
	virtual AsciiString rva004B8851() const;
};
AsciiString Rva004B8732::rva004B8851() const
{
	return m_moduleData->m_08;
}
