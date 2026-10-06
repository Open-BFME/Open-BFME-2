// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva00423A4A@@QAE@PAURva00423A4A_Range@@@Z retail 0x00423A4A 30B
// Holder ctor over a vector<BfmeE12*> at +0: range-construct from the
// caller's first/last pair via the rowed range ctor at 0x00423519.
// Evidence: chain lane (calls 0x00423519 just landed) plus caller 0x00423E83.
#include <vector>

struct BfmeE12 { float x, y, z; };

struct Rva00423A4A_Range
{
	BfmeE12 **first;
	BfmeE12 **last;
};

struct Rva00423A4A
{
	_STL::vector<BfmeE12 *> m_vec;
	Rva00423A4A(Rva00423A4A_Range *r);
};

Rva00423A4A::Rva00423A4A(Rva00423A4A_Range *r) : m_vec(r->first, r->last) {}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0Rva00423A4A@@QAE@ABU0@@Z=??0Rva00423A4A@@QAE@PAURva00423A4A_Range@@@Z")
