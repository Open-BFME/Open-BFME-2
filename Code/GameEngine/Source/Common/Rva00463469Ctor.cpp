// cl: /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ??0Rva00463469@@QAE@I@Z @0x00463469 (36B):
// Single-proxy ctor: _STLP_alloc_proxy<unsigned int,int,allocator<int> > at +0
// via rowed 0x0014F3C4 with (default alloc 0) then _M_data holds the 0x60-byte
// block from rowed allocator<char>::allocate 0x000307F0. Evidence: linkbody lane
// push-ecx plus lea-esp-B plus 0x60 shape 17 insns exact as Rva004D9A8B 0x004D9A8B
// (36B with 0x38) and Rva00434942 0x00434942 (39B with 0xE08); unblocks 0x00463736
// caller 0x0046373D; LINK BONUS 468B via 0x00463736.
#include <deque>

class Rva00463469
{
public:
	Rva00463469(unsigned dummy);
private:
	_STL::_STLP_alloc_proxy<unsigned int, int, _STL::allocator<int> > m_proxy;
};

Rva00463469::Rva00463469(unsigned) : m_proxy(_STL::allocator<int>(), 0)
{
	m_proxy._M_data = (unsigned int)_STL::allocator<char>::allocate(0x60, 0);
}
