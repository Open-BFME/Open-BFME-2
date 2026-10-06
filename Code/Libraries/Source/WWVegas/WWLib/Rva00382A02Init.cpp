// cl: /D_STLP_NO_EXCEPTIONS /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ??0Rva00382A02@@QAE@H@Z 0x00382A02 36B
// Ctor: proxy at +0 init to null via tmp allocator then allocate 52B into it.
// Evidence: calls 0x0014F3C4 proxy and 0x000307F0 allocate; caller 0x001DD81C passes through.
#include <deque>
#include <memory>

class Rva00382A02
{
public:
	_STL::_STLP_alloc_proxy<unsigned*, unsigned, _STL::allocator<unsigned> > m_proxy;
	Rva00382A02(int unused);
};

Rva00382A02::Rva00382A02(int unused)
	: m_proxy(_STL::allocator<unsigned>(), (unsigned*)0)
{
	m_proxy._M_data = (unsigned*)_STL::allocator<char>::allocate(52, 0);
}

class Rva001DD81C
{
	Rva00382A02 m0;
	int m4;
public:
	Rva001DD81C(int a, int b);
};

Rva001DD81C::Rva001DD81C(int a, int b)
	: m0(b)
{
	unsigned* buf = m0.m_proxy._M_data;
	m4 = 0;
	((char*)buf)[0] = 0;
	((int*)m0.m_proxy._M_data)[1] = 0;
	((void**)m0.m_proxy._M_data)[2] = m0.m_proxy._M_data;
	((void**)m0.m_proxy._M_data)[3] = m0.m_proxy._M_data;
}
