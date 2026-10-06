// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??$__lower_bound@U?$_Deque_iterator@UBfmeE12@@U?$_Nonconst_traits@UBfmeE12@@@_STL@@@_STL@@MUBfmeE12Cmp0042299E@@H@_STL@@YA?AU?$_Deque_iterator@UBfmeE12@@U?$_Nonconst_traits@UBfmeE12@@@_STL@@@0@U10@0ABMUBfmeE12Cmp0042299E@@PAH@Z @0x0042299E (122B):
// Binary search over deque<BfmeE12> iterators with float key by const ref;
// retail compares float key vs element y (+4) with comiss, calls _M_subtract,
// _M_advance, _M_increment. Caller 0x00422FE6 passes val+comp+0.
// Evidence: unlock lane, all callees rowed, unblocks 0x00422FE6.
//
// ??$lower_bound@U?$_Deque_iterator@UBfmeE12@@U?$_Nonconst_traits@UBfmeE12@@@_STL@@@_STL@@MUBfmeE12Cmp0042299E@@@_STL@@YA?AU?$_Deque_iterator@UBfmeE12@@U?$_Nonconst_traits@UBfmeE12@@@_STL@@@0@U10@0ABMUBfmeE12Cmp0042299E@@@Z @0x00422FE6 (55B):
// Chain wrapper forwarding to 0x0042299E with distance 0.
// Evidence: chain lane, callee just landed, caller 0x004233F5.
#include <algorithm>
#include <deque>
struct BfmeE12 { float x, y, z; };
struct BfmeE12Cmp0042299E
{
	__forceinline bool operator()(const BfmeE12 &a, const float &b) const { return a.y < b; }
};
template _STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> > _STL::__lower_bound<_STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, float, BfmeE12Cmp0042299E, int>(_STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, _STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, const float &, BfmeE12Cmp0042299E, int *);
template _STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> > _STL::lower_bound<_STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, float, BfmeE12Cmp0042299E>(_STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, _STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, const float &, BfmeE12Cmp0042299E);
