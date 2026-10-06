// ??0Rva005CB35A@@QAE@XZ
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ??0Rva005CB35A@@QAE@XZ @0x005CB35A 100B.
// Ctor of class Rva005CB35A (dtor rowed at 0x005CB3BE: six pointers at
// +0x08..+0x1C released through 0x36410, then an 8-byte polymorphic first
// member through 0x22167C). Shape taken from the matched sibling
// Rva005E74CF.cpp: SEH prologue, double push ecx, push esi/edi, mov esi,ecx,
// push 0xC74D98, temp AsciiString at [ebp-0x10], mov [ebp-0x14],esi,
// StringBase ctor 0x37BA0, base ctor 0x221635, state byte 2, release
// 0x36410, then the derived vptr store and the six zero stores.
//
// The whole of the previous attempt's gap was the explicit
// `*(const void **)this = g_00C74D90;` in the body: MSVC /O1 sinks that DIR32
// constant store BELOW all six register zero-stores, while retail emits the
// vptr store FIRST. Declaring the ctor with no explicit vtable assignment --
// exactly as the byte-matching Rva005E74CF does -- lets the compiler emit the
// derived vptr from the class's own vftable, which it places first. The
// six zeroes stay one member subobject so they land as a unit after it.
#include "ascii_string.h"

class Rva00221635
{
public:
	Rva00221635(int arg);
	~Rva00221635();
	virtual void _pure() = 0;
	int m_4;
};

struct Rva005CB35AM8
{
	void *m_8;
	void *m_c;
	void *m_10;
	void *m_14;
	void *m_18;
	void *m_1c;
	Rva005CB35AM8()
	{
		m_8 = 0;
		m_c = 0;
		m_10 = 0;
		m_14 = 0;
		m_18 = 0;
		m_1c = 0;
	}
};

class Rva005CB35A : public Rva00221635
{
public:
	Rva005CB35A();

private:
	Rva005CB35AM8 m_08;
};

// ??0Rva005CB35A@@QAE@XZ
Rva005CB35A::Rva005CB35A()
	: Rva00221635((int)&AsciiString("RegionDisplay"))
{
}