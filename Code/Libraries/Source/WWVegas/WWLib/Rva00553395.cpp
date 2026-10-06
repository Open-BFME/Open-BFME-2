// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva00553395@@QAE@I@Z @0x00553395 39B: Single-proxy ctor _STLP_alloc_proxy at +0 via rowed 0x0014F3C4 with (default alloc 0) then 0x55C-byte block via rowed allocator<char>::allocate 0x000307F0. Evidence: unlock lane unblocks 0x00553890 caller 0x00553897 same push-ecx lea-esp-B shape as Rva00434942 0x00434942 (39B with 0xE08) plus Rva004D9A8B 0x004D9A8B (36B with 0x38).
#include <deque>

class Rva00553395
{
public:
	Rva00553395(unsigned dummy);
private:
	_STL::_STLP_alloc_proxy<unsigned int, int, _STL::allocator<int> > m_proxy;
};

Rva00553395::Rva00553395(unsigned) : m_proxy(_STL::allocator<int>(), 0)
{
	m_proxy._M_data = (unsigned int)_STL::allocator<char>::allocate(0x55C, 0);
}
