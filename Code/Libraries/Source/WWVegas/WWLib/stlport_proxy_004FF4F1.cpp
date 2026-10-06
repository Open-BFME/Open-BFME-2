// cl: /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ??0Rva004FF4F1@@QAE@I@Z @0x004FF4F1 36B: Single-proxy ctor _STLP_alloc_proxy at +0 via rowed 0x0014F3C4 with (default alloc 0) then 0x28-byte block via rowed allocator<char>::allocate 0x000307F0. Evidence: unlock lane same push-ecx lea-esp-B 17-insn shape as Rva004D9A8B 0x004D9A8B (36B with 0x38) and Rva00463469 0x00463469 (36B with 0x60); callers 0x004FF6AB 42B empty-tree init and 0x00501E88 165B copy.
#include <deque>

class Rva004FF4F1
{
public:
	Rva004FF4F1(unsigned dummy);
private:
	_STL::_STLP_alloc_proxy<unsigned int, int, _STL::allocator<int> > m_proxy;
};

Rva004FF4F1::Rva004FF4F1(unsigned) : m_proxy(_STL::allocator<int>(), 0)
{
	m_proxy._M_data = (unsigned int)_STL::allocator<char>::allocate(0x28, 0);
}
