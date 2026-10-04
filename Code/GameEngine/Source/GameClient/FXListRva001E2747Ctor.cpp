// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /O1 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva001E2747@@QAE@ABVAsciiString@@@Z @0x001E2747 127B ctor taking name.
// Retail stores vtable 0x7DD970, default-builds two list<int> members at +4
// and +0x18 via rowed 0x4EC36C, copies AsciiString at +0xC via pinned 0x365F0,
// zeroes +8/+0x10/+0x14/+0x24, sets +0x1C=30 +0x20=60, clears +0x18 via rowed
// 0x23DAA5. Callers at 0x1E28BF (derived) and 0x1E2D69 (new 0x28 + initFromINI
// with FXList table 0x7DC720) prove the AsciiString arg and 0x28 size.

#include <list>

#include "ascii_string.h"


class FXList
{
public:
	void clear();
};

class Rva001E2747 : public FXList
{
public:
	Rva001E2747(const AsciiString &name);
	virtual ~Rva001E2747();
private:
	_STL::list<int, _STL::allocator<int> > m_list04; // +0x04
	unsigned char m_field08; // +0x08
	AsciiString m_string0C; // +0x0C
	unsigned char m_field10; // +0x10
	int m_field14; // +0x14
	_STL::list<int, _STL::allocator<int> > m_list18; // +0x18
	int m_field1C; // +0x1C = 30
	int m_field20; // +0x20 = 60
	unsigned char m_field24; // +0x24
};

Rva001E2747::Rva001E2747(const AsciiString &name) :
	m_string0C(name),
	m_field10(0)
{
	m_field08 = 0;
	m_field14 = 0;
	m_field1C = 30;
	m_field20 = 60;
	m_list18.clear();
	m_field24 = 0;
}

Rva001E2747::~Rva001E2747()
{
	((FXList *)(void *)this)->clear();
}
