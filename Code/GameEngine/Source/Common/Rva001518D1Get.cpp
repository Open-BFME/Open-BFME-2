// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva001518D1@Rva001518D1@@QAEPAV?$vector@UBfmeE16@@V?$allocator@UBfmeE16@@@_STL@@@_STL@@XZ at 0x001518D1 (68B).
// Getter returning link vector at +0x0C or static empty vector<BfmeE16>.
// First deref +0 then +0x14 link proven by Rva00151632/Rva001517DE layout,
// fallback constructs empty via rowed Vector_base 0x00211E58 plus atexit
// row 0x006291F8. Caller 0x001526C1 proves getter shape.
#include <vector>

struct BfmeE16 { float x, y, z, w; };

class Link
{
public:
	char m_pad00[0x0C];
	_STL::vector<BfmeE16> m_vec; // +0x0C
};

class Mid
{
public:
	char m_pad00[0x14];
	Link *m_link; // +0x14
};

class Rva001518D1
{
public:
	_STL::vector<BfmeE16> *rva001518D1();
private:
	Mid *m_ptr; // +0
};

_STL::vector<BfmeE16> *Rva001518D1::rva001518D1()
{
	if (m_ptr != 0 && m_ptr->m_link != 0)
		return &m_ptr->m_link->m_vec;
	static _STL::vector<BfmeE16> empty;
	return &empty;
}
