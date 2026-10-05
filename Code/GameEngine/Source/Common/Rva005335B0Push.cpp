// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva005335B0@Rva005335B0@@QAEXGG@Z @0x005335B0 35B.
// Tiny thiscall building a 4B Rva005334A4Element from two words then
// push_back to the vector at +0x38. Evidence: rowed push_back 0x005334A4
// callee; caller 0x005337CA in 1173B unclaimed; neighbours 0x005334A4 STL
// flags and 0x005335D3 reset share the page.
#include <vector>

struct Rva005334A4Element
{
	unsigned short x;
	unsigned short y;
};

class Rva005335B0
{
public:
	void rva005335B0(unsigned short a, unsigned short b);
private:
	char m_pad[0x38];
	_STL::vector<Rva005334A4Element> m_vec;
};

void Rva005335B0::rva005335B0(unsigned short a, unsigned short b)
{
	Rva005334A4Element tmp;
	tmp.x = a;
	tmp.y = b;
	m_vec.push_back(tmp);
}
