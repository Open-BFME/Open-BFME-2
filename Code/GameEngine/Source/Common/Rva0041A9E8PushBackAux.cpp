// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva0041A9E8@Rva0041A9E8@@QAEXABUBfmeNarrowRecord0041A617@@@Z @0x0041A9E8,
// 135B: deque push-back slow path for 16B narrow record. Temp-copies via
// rowed copy 0x0041A617, reserves via rowed PAX 0x002F1F19, allocates 0x80
// via rowed byte 0x000307F0, constructs via rowed 0x0041A727, reloads finish
// (node+1 first last cur with +8) and frees temp buffer via rowed _free
// 0x00030830. Evidence: pin deque Pod16 aux, caller push_back 0x0041ABB9,
// same shape as rowed 28B wrapper 0x0041A96D with 0x70/+4.
// Retail's unwind map destroys the temporary copy (state 0) and disarms it
// right after the construct; the temporary's own string teardown frees the
// buffer. The disarm store survives only under /EHs (the extern "C" free is
// otherwise treated as non-throwing); the banked attempt also freed the
// buffer a second time by hand.
#include <memory>
#include <string>

extern "C" void __cdecl free(void *ptr);

#include "BfmeNarrowRecord0041A617.h"

namespace _STL {
template <class _Tp, class _Alloc> class deque {
protected:
    void _M_reserve_map_at_back(unsigned);
};
}

struct Rva0041A9E8 : _STL::deque<void *, _STL::allocator<void *> > {
    unsigned char m_pad0[0x10];
    BfmeNarrowRecord0041A617 *_M_cur10;
    BfmeNarrowRecord0041A617 *_M_first14;
    BfmeNarrowRecord0041A617 *_M_last18;
    BfmeNarrowRecord0041A617 **_M_node1C;
    void rva0041A9E8(const BfmeNarrowRecord0041A617 &x);
};

void Rva0041A9E8::rva0041A9E8(const BfmeNarrowRecord0041A617 &x)
{
	BfmeNarrowRecord0041A617 tmp(x);
	_M_reserve_map_at_back(1);
	_M_node1C[1] = (BfmeNarrowRecord0041A617 *)_STL::allocator<char>::allocate(0x80, 0);
	_STL::_Construct(_M_cur10, tmp);
	BfmeNarrowRecord0041A617 **node = _M_node1C + 1;
	_M_node1C = node;
	_M_first14 = *node;
	_M_last18 = _M_first14 + 8;
	_M_cur10 = _M_first14;
}
