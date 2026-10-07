// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva004045B4@Rva004045B4@@QAEXXZ retail 0x004045B4 148B
// Search vector for id then update or append 20B record with float and
// vector<AsciiString>. Callers unclaimed. Evidence: rowed ctor 0x0040394A
// plus rowed push_back 0x0040457D plus vector assign/dtor rows.
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

#include "ascii_string.h"

class Rva00403927
{
public:
	int m_id;
	float m_val;
	_STL::vector<AsciiString> m_strs;
};

class Rva0040394A
{
public:
	Rva0040394A();
	int m_id;
	float m_val;
	_STL::vector<AsciiString> m_strs;
};

class Rva004045B4 : public _STL::vector<Rva00403927>
{
public:
	void rva004045B4(int id, float val, const _STL::vector<AsciiString> *strs);
};

void Rva004045B4::rva004045B4(int id, float val, const _STL::vector<AsciiString> *strs)
{
	for (Rva00403927 *p = &(*begin()); p != &(*end()); ++p) {
		if (p->m_id == id) {
			p->m_val = val;
			if (strs)
				p->m_strs = *strs;
			return;
		}
	}
	Rva0040394A tmp;
	tmp.m_id = id;
	tmp.m_val = val;
	if (strs)
		tmp.m_strs = *strs;
	push_back((const Rva00403927 &)tmp);
}
