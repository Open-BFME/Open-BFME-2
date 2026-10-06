// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva003F8ED6@@QAE@H@Z @0x003F8EA2 52B.
// Ctor of Rva003F8ED6: stores arg at +4 via base, 13 at +8, constructs
// vector<BfmeE16> at +0xC, nulls AsciiString at +0x18 and holder at +0x1C.
// Evidence: unlock lane; vtable 0x00837358 same as dtor 0x003F8ED6/??_G 0x003F905F;
// callee Vector_base<BfmeE16> 0x00211E58 rowed; caller 0x003F8F2B pushes [esi+4]
// for 0x20-byte new; layout matches Rva003F8ED6.cpp (vector at +0xC).
#include <vector>

#include "ascii_string.h"

struct BfmeE16 { float x, y, z, w; };

struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct TargetRefHolder1C
{
	TargetRefHolder1C() : m_ptr(0) {}
	~TargetRefHolder1C() { if (m_ptr) ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr); }
	void *m_ptr;
};

struct __declspec(novtable) Base003F8ED6
{
	virtual ~Base003F8ED6() {}
	Base003F8ED6(int x) : m_04(x) {}
	int m_04;
};

class Rva003F8ED6 : public Base003F8ED6
{
public:
	Rva003F8ED6(int x);
	virtual ~Rva003F8ED6();
	int m_08;
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_0C;
	AsciiString m_18;
	TargetRefHolder1C m_1C;
};

Rva003F8ED6::Rva003F8ED6(int x) : Base003F8ED6(x), m_08(13), m_0C(), m_18(), m_1C()
{
}
