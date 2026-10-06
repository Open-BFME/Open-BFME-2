// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /DNDEBUG
// stlport
// ??0Rva003F610FElement@@QAE@ABU0@@Z @ 0x003F54DC 84B: copy ctor (int plus vector<int> plus vector<BfmePod104> plus 5 dwords)
// Evidence: called by just-landed _Construct at 0x003F583E; member layout mirrors VectorMemberRecordDtors with BfmePod104 view for the rowed vector copy ctor.
#include <vector>

struct BfmePod104 { int a[26]; };

struct RvaTail20 { int w[5]; };

struct Rva003F610FElement
{
	Rva003F610FElement(const Rva003F610FElement &src);
	int m_00;
	_STL::vector<unsigned int> m_04;
	_STL::vector<BfmePod104> m_10;
	RvaTail20 m_1C;
};

Rva003F610FElement::Rva003F610FElement(const Rva003F610FElement &src)
	: m_00(src.m_00)
	, m_04(src.m_04)
	, m_10(src.m_10)
	, m_1C(src.m_1C)
{
}
