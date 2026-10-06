// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// SimpleObjectIterator::insert (WorldBuilder name, SimpleObjectIterator.cpp line 62: deque push_back of the pair); 0x0054B414 (deque clear) is on the same class.
// stlport
//
// was ?rva0054BBB5@Rva0054BBB5@@QAEXHM@Z, retail 0x0054BBB5, 37 bytes.
// Packs (int, float) into BfmeE8 temp and deque push_back at this+0x14.
// Evidence: prev 0x0054B850 deque push_back rowed, retail movss plus
// lea [ebp-8] plus add ecx 0x14 plus ret 8, 15 callers.

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

#include <deque>

struct BfmeE8
{
	int a;
	float b;
};

class SimpleObjectIterator
{
public:
	void insert(int a, float b);
	void rva0054B414();

private:
	unsigned char m_pad00[0x14];
	_STL::deque<BfmeE8> m_deque;
};

void SimpleObjectIterator::insert(int a, float b)
{
	BfmeE8 tmp;
	tmp.a = a;
	tmp.b = b;
	m_deque.push_back(tmp);
}

void SimpleObjectIterator::rva0054B414()
{
	return m_deque.clear();
}
