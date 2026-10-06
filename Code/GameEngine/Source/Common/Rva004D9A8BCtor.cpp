// cl: /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ??0Rva004D9A8B@@QAE@I@Z @0x004D9A8B (36B):
// Single-proxy ctor: _STLP_alloc_proxy<unsigned int,int,allocator<int> > at +0
// via rowed 0x0014F3C4 with (default alloc, 0), then _M_data holds the 0x38-byte
// block from rowed allocator<char>::allocate 0x000307F0. Evidence: unlock lane,
// push-ecx plus lea-esp-B plus 0x38 shape, 17 insns exact, unblocks 0x004D9B18,
// caller 0x004D9B1F.
#include <deque>

class Rva004D9A8B
{
public:
	Rva004D9A8B(unsigned dummy);
private:
	_STL::_STLP_alloc_proxy<unsigned int, int, _STL::allocator<int> > m_proxy;
};

Rva004D9A8B::Rva004D9A8B(unsigned) : m_proxy(_STL::allocator<int>(), 0)
{
	m_proxy._M_data = (unsigned int)_STL::allocator<char>::allocate(0x38, 0);
}
