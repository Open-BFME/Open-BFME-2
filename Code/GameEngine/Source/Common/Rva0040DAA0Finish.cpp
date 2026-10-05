// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii
// stlport
// ?rva0040DAA0@Rva0040DAA0@@QBEPAXABV?$StringBase@D@@PAH@Z, retail 0x0040DAA0, 80 bytes.
// thiscall (mov esi,ecx; ret 8). Linear find by string over the 0x40-anchored
// _STL::vector<Rva0040DAA0Entry>: m_vec[i] is an 8-byte {int, target*} record,
// the target's StringBase<char> at +4 compared via the rowed 0x0069D6; returns
// the entry target and, optionally, its index. Evidence: caller bfmeGo1034A
// 0x0040DAF0 rel32; the sibling range find Rva00404D70 in this directory uses
// the same _STL::vector size() loop bound.
#include "ascii_string.h"
#include <vector>

struct Rva0040DAA0Target
{
	char m_pad00[4];
	StringBase<char> m_name;
};

struct Rva0040DAA0Entry
{
	int m_first;
	Rva0040DAA0Target *m_second;
};

class Rva0040DAA0
{
public:
	void *rva0040DAA0(const StringBase<char> &name, int *indexOut) const;
private:
	char m_pad[0x40];
	_STL::vector<Rva0040DAA0Entry> m_vec;
};

void *Rva0040DAA0::rva0040DAA0(const StringBase<char> &name, int *indexOut) const
{
	for (unsigned int i = 0; i < m_vec.size(); ++i) {
		Rva0040DAA0Target *t = m_vec[i].m_second;
		if (t->m_name.compare(name) == 0) {
			if (indexOut)
				*indexOut = (int)i;
			return m_vec[i].m_second;
		}
	}
	return 0;
}
