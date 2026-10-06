// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva00553890@@QAE@II@Z @0x00553890 42B: Derived ctor calls base Rva00553395 0x00553395 with second arg then zeroes +4 and buffer header byte +0 dword +4 plus self links +8 +0xC. Evidence: chain lane base now rowed plus caller 0x00558D7A plus unblocks 0x00558D6B.
#include <deque>
class Rva00553395
{
public:
	Rva00553395(unsigned dummy);
protected:
	_STL::_STLP_alloc_proxy<unsigned int, int, _STL::allocator<int> > m_proxy;
};
struct Rva00553890Buf
{
	unsigned char b00;
	char pad01[3];
	unsigned int u04;
	Rva00553890Buf *p08;
	Rva00553890Buf *p0C;
};
class Rva00553890 : public Rva00553395
{
	unsigned m_u04;
public:
	Rva00553890(unsigned a, unsigned b);
};
Rva00553890::Rva00553890(unsigned a, unsigned b) : Rva00553395(b)
{
	m_u04 = 0;
	((Rva00553890Buf *)m_proxy._M_data)->b00 = 0;
	((Rva00553890Buf *)m_proxy._M_data)->u04 = 0;
	((Rva00553890Buf *)m_proxy._M_data)->p08 = (Rva00553890Buf *)m_proxy._M_data;
	((Rva00553890Buf *)m_proxy._M_data)->p0C = (Rva00553890Buf *)m_proxy._M_data;
}
