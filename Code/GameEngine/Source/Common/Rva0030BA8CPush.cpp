// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0030BA8C@Rva0030BA8C@@QAEXABUBfmeE8@@@Z, retail 0x0030BA8C, 20 bytes.
// Holder push via rowed vector E8 push_back 0x00539A2E plus flag at +0x24 set to 1.
// Evidence: callers 0x0030BAB7 0x003290F7 0x00330AC8; prev clear 0x0030B9CA same flags next Disp8Lea no-flags.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>
struct BfmeE8 { int a[2]; };

struct Rva0030BA8C
{
	void rva0030BA8C(const BfmeE8 &val);
	_STL::vector<BfmeE8, _STL::allocator<BfmeE8> > m_vec;
	char m_pad[0x24 - 12];
	bool m_flag;
};

void Rva0030BA8C::rva0030BA8C(const BfmeE8 &val)
{
	m_vec.push_back(val);
	m_flag = true;
}
