// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva0041A96D@Rva0041A96D@@QAEXABUBfmeNarrowRecord0041A5D2@@@Z @0x0041A96D,
// 123B: record-deque push-back slow path. Temp-copies the value via rowed
// copy ctor 0x0041A5D2, reserves with the size-shared rowed BfmePod28
// _M_reserve_map_at_back 0x0041A35C (both elements are 28B), allocates a
// 0x70 node via rowed byte allocate 0x000307F0, constructs via rowed
// _Construct 0x0041A6FA, reloads finish (node+1, first, last, cur) and
// destroys the temp via rowed dtor 0x0041A200. Minimal deque base exists
// only to reach the protected reserve spelling; empty-base layout keeps
// the finish fields at +0x10.
#include <memory>
#include <string>
struct BfmePod28 { int a[7]; };
namespace _STL {
template <class _Tp, class _Alloc> class deque {
protected:
    void _M_reserve_map_at_back(unsigned);
};
}
#include "BfmeNarrowRecord0041A5D2.h"
struct Rva0041A96D : _STL::deque<BfmePod28, _STL::allocator<BfmePod28> > {
    unsigned char m_pad0[0x10];
    BfmeNarrowRecord0041A5D2 *_M_cur10;
    BfmeNarrowRecord0041A5D2 *_M_first14;
    BfmeNarrowRecord0041A5D2 *_M_last18;
    BfmeNarrowRecord0041A5D2 **_M_node1C;
    void rva0041A96D(const BfmeNarrowRecord0041A5D2 &x);
    void rva0041AB68(const BfmeNarrowRecord0041A5D2 &x);
};
void Rva0041A96D::rva0041A96D(const BfmeNarrowRecord0041A5D2 &x)
{
	BfmeNarrowRecord0041A5D2 tmp(x);
	_M_reserve_map_at_back(1);
	_M_node1C[1] = (BfmeNarrowRecord0041A5D2 *)_STL::allocator<char>::allocate(0x70, 0);
	_STL::_Construct(_M_cur10, tmp);
	BfmeNarrowRecord0041A5D2 **node = _M_node1C + 1;
	_M_node1C = node;
	_M_first14 = *node;
	_M_last18 = _M_first14 + 4;
	_M_cur10 = _M_first14;
}
void Rva0041A96D::rva0041AB68(const BfmeNarrowRecord0041A5D2 &x)
{
	if (_M_cur10 != _M_last18 - 1)
	{
		_STL::_Construct(_M_cur10, x);
		++_M_cur10;
	}
	else
		rva0041A96D(x);
}
