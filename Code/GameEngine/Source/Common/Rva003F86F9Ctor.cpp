// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva003F86F9@@QAE@HH@Z @0x003F86F9 47B.
// Ctor of unknown class with vtable 0x00837314: stores two int args at +4/+8,
// then constructs vector<BfmeE16> at +0xC via rowed Vector_base 0x00211E58,
// then sets dword at +0x18 to -1.
// Evidence: leaf lane; callees all rowed; caller 0x003F9147 unclaimed;
// layout matches sibling Rva003F877E ctor (vector at +0xC, same flags);
// base-before-vtable order proves 2-int base; ret 8 with ecx=this proves HH.
#include <vector>

struct BfmeE16 { float x, y, z, w; };

struct Base003F86F9
{
	Base003F86F9(int a, int b) : m_04(a), m_08(b) {}
	int m_04;
	int m_08;
};

class Rva003F86F9 : public Base003F86F9
{
public:
	Rva003F86F9(int a, int b);
	virtual ~Rva003F86F9();
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_0C;
	int m_18;
};

Rva003F86F9::Rva003F86F9(int a, int b) : Base003F86F9(a, b), m_0C(), m_18(-1)
{
}
