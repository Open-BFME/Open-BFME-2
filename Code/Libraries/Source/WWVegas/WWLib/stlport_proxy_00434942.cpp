// cl: /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ??0Rva00434942@@QAE@I@Z @0x00434942 39B: Single-proxy ctor _STLP_alloc_proxy at +0 via rowed 0x0014F3C4 with (default alloc 0) then 0xE08-byte block via rowed allocator<char>::allocate 0x000307F0. Evidence: unlock lane unblocks 0x00434C3D caller 0x00434C44 same push-ecx lea-esp-B shape as Rva004D9A8B 0x004D9A8B (36B with 0x38) plus 3B push-imm32 delta = 39B.
#include <deque>

class Rva00434942
{
public:
	Rva00434942(unsigned dummy);
private:
	_STL::_STLP_alloc_proxy<unsigned int, int, _STL::allocator<int> > m_proxy;
};

Rva00434942::Rva00434942(unsigned) : m_proxy(_STL::allocator<int>(), 0)
{
	m_proxy._M_data = (unsigned int)_STL::allocator<char>::allocate(0xE08, 0);
}
