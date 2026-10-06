// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva003F877E@@QAE@HH@Z @0x003F877E 43B.
// Ctor of unknown class with vtable 0x00837318: stores two int args at +4/+8,
// then constructs vector<BfmeE16> at +0xC via rowed Vector_base 0x00211E58.
// Evidence: leaf lane; callees all rowed; caller 0x003F91FB unclaimed;
// layout matches sibling Rva003F8ED6 ctor (vector at +0xC, same flags);
// base-before-vtable order proves 2-int base; ret 8 with ecx=this proves HH.
#include <vector>

struct BfmeE16 { float x, y, z, w; };

struct Base003F877E
{
	Base003F877E(int a, int b) : m_04(a), m_08(b) {}
	int m_04;
	int m_08;
};

class Rva003F877E : public Base003F877E
{
public:
	Rva003F877E(int a, int b);
	virtual ~Rva003F877E();
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_0C;
};

Rva003F877E::Rva003F877E(int a, int b) : Base003F877E(a, b), m_0C()
{
}
