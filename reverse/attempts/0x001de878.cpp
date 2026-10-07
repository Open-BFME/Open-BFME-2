// ??0Rva001DF2D3Element@@QAE@ABU0@@Z
// partial score=0.99 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??0Rva001DF2D3Element@@QAE@ABU0@@Z @0x001DE878 113B element copy constructor.
// Target evidence: callers invoke this address for Rva001DF2D3Element; retail copies five words, then the tree at +0x14, vector at +0x20, and three flags at +0x2C.
// Donor provenance: tree and vector member copy operations follow the rowed callees; the class name and unconstrained fields remain address-derived from matched callers.
#define _STLP_NO_EXCEPTIONS 1
#include <map>
#include <vector>

struct BfmeRecord001DD3BC
{
	unsigned char m_data[8];
};

bool operator<(const BfmeRecord001DD3BC &, const BfmeRecord001DD3BC &);
typedef _STL::_Rb_tree<BfmeRecord001DD3BC, BfmeRecord001DD3BC,
	_STL::_Identity<BfmeRecord001DD3BC>, _STL::less<BfmeRecord001DD3BC>,
	_STL::allocator<BfmeRecord001DD3BC> > BfmeRecord001DD3BCSetTree;

enum ScienceType
{
	SCIENCE_NONE = 0
};

struct Rva001DF2D3Element
{
public:
	Rva001DF2D3Element(const Rva001DF2D3Element &that);

private:
	unsigned int m_word0;
	unsigned int m_word1;
	unsigned int m_word2;
	unsigned int m_word3;
	unsigned int m_word4;
	BfmeRecord001DD3BCSetTree m_records;
	_STL::vector<ScienceType> m_sciences;
	bool m_flag0;
	bool m_flag1;
	bool m_flag2;
};

typedef char Rva001DF2D3ElementSizeCheck[sizeof(Rva001DF2D3Element) == 0x30 ? 1 : -1];

Rva001DF2D3Element::Rva001DF2D3Element(const Rva001DF2D3Element &that)
	: m_word0(that.m_word0)
	, m_word1(that.m_word1)
	, m_word2(that.m_word2)
	, m_word3(that.m_word3)
	, m_word4(that.m_word4)
	, m_records(that.m_records)
	, m_sciences(that.m_sciences)
	, m_flag0(that.m_flag0)
	, m_flag1(that.m_flag1)
	, m_flag2(that.m_flag2)
{
}
