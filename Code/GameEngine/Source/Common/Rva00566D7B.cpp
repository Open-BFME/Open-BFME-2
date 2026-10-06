// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva00566D7B@Rva00566D7B@@QAEXABVRva004E32F2@@@Z retail 0x00566D7B 8B
// Evidence: chain lane callee push_back Rva004E32F2 0x00566BB4; add ecx 0x60 plus jmp tail same shape as rowed 0x00566AB7.
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
class Rva004E32F2
{
public:
	Rva004E32F2(const Rva004E32F2 &o);
	virtual ~Rva004E32F2();
private:
	char m_pad[0x14];
};
class Rva00566D7B
{
public:
	void rva00566D7B(const Rva004E32F2 &v);
private:
	char m_pad00[0x60];
	_STL::vector<Rva004E32F2> m_vec60;
};
void Rva00566D7B::rva00566D7B(const Rva004E32F2 &v)
{
	m_vec60.push_back(v);
}
