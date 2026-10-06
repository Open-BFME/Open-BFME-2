// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva0002CBB4@Rva0002CBB4@@QAEXABVAsciiString@@@Z @0x0002CBB4 24B
// Wrapper that inserts into a nocase AsciiString set member at +0x14.
// Evidence: calls the rowed set::insert at 0x0002CA26 (which calls the rowed
// tree insert_unique at 0x0002C908); result discarded (ret 4); no callers,
// host class opaque so honest-address name used.
#define _STLP_NO_EXCEPTIONS 1
#include <set>

#include "ascii_string.h"

struct BfmeStringNoCaseLess
{
	bool operator()(const AsciiString &a, const AsciiString &b) const;
};

class Rva0002CBB4
{
	unsigned char m_pad[0x14];

public:
	_STL::set<AsciiString, BfmeStringNoCaseLess, _STL::allocator<AsciiString> > m_set;
	void rva0002CBB4(const AsciiString &v);
};

void Rva0002CBB4::rva0002CBB4(const AsciiString &v)
{
	m_set.insert(v);
}
