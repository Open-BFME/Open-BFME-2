// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva0037D076@@QAE@XZ @0x0037D076 (33B).
// No-arg ctor: list<int> at +0x4 via rowed _List_base 0x004EC36C with empty
// allocator from stack, int at +0x8 set to -1 via or, bytes at +0/+0x1 cleared.
// Caller at 0x0037D2CC in 0x0037D1E6 news 0xC and runs this ctor. Flags copy
// next sibling FXListNuggetParse.cpp (bfmelist plus bfmealloc plus NO_EXCEPTIONS
// for EH-free list ctor). Owner unproven so honest-address class Rva0037D076.
#include <list>
class Rva0037D076
{
	unsigned char m_b0;
	unsigned char m_b1;
	char m_pad2[2];
	_STL::list<int> m_list;
	int m_i8;
public:
	Rva0037D076();
};
Rva0037D076::Rva0037D076()
{
	m_i8 = -1;
	m_b1 = 0;
	m_b0 = 0;
}
