// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??$__unguarded_partition@U?$_Deque_iterator@UBfmeE12@@U?$_Nonconst_traits@UBfmeE12@@@_STL@@@_STL@@UBfmeE12@@UBfmeE12Cmp00422291@@@_STL@@YA?AU?$_Deque_iterator@UBfmeE12@@U?$_Nonconst_traits@UBfmeE12@@@_STL@@@0@U10@0UBfmeE12@@UBfmeE12Cmp00422291@@@Z @0x00422217 (122B):
// __unguarded_partition over deque<BfmeE12> iterators with BfmeE12 pivot by
// value plus comparator; retail compares the float at +4 with comiss,
// calls _M_decrement, _M_increment, iterator operator< and BfmeE12 swap.
// Evidence: unlock lane, all callees rowed, caller 0x00424AE0, neighbours
// share // cl: with deque_e12_sort.
//
// ??$__push_heap@U?$_Deque_iterator@UBfmeE12@@U?$_Nonconst_traits@UBfmeE12@@@_STL@@@_STL@@HUBfmeE12@@UBfmeE12Cmp00422291@@@_STL@@YAXU?$_Deque_iterator@UBfmeE12@@U?$_Nonconst_traits@UBfmeE12@@@_STL@@@0@HHUBfmeE12@@UBfmeE12Cmp00422291@@@Z @0x004222F9 (126B):
// __push_heap sift-up over deque<BfmeE12>; parent (hole-1)/2, comiss on y,
// operator+ rowed, 12B shifts, final store. Caller 0x00422C5A.
// Evidence: unlock lane, all callees rowed, unblocks 0x00422B98.
//
// ??$__adjust_heap@U?$_Deque_iterator@UBfmeE12@@U?$_Nonconst_traits@UBfmeE12@@@_STL@@@_STL@@HUBfmeE12@@UBfmeE12Cmp00422291@@@_STL@@YAXU?$_Deque_iterator@UBfmeE12@@U?$_Nonconst_traits@UBfmeE12@@@_STL@@@0@HHUBfmeE12@@UBfmeE12Cmp00422291@@@Z @0x00422B98 (207B):
// __adjust_heap sift-down plus push_heap tail call; cmova pick, 12B shifts.
// Callers 0x004232CA 0x00423335. Evidence: chain lane, callee just landed.
//
// ??$__make_heap@U?$_Deque_iterator@UBfmeE12@@U?$_Nonconst_traits@UBfmeE12@@@_STL@@@_STL@@UBfmeE12Cmp00422291@@UBfmeE12@@H@_STL@@YAXU?$_Deque_iterator@UBfmeE12@@U?$_Nonconst_traits@UBfmeE12@@@_STL@@@0@0UBfmeE12Cmp00422291@@PAUBfmeE12@@PAH@Z @0x004232D6 (115B):
// __make_heap build loop calling adjust_heap; (len-2)/2 down to 0.
// Caller 0x004239B4. Evidence: chain lane, callee just landed.
//
// ??$__pop_heap@U?$_Deque_iterator@UBfmeE12@@U?$_Nonconst_traits@UBfmeE12@@@_STL@@@_STL@@UBfmeE12@@UBfmeE12Cmp00422291@@H@_STL@@YAXU?$_Deque_iterator@UBfmeE12@@U?$_Nonconst_traits@UBfmeE12@@@_STL@@@0@00UBfmeE12@@UBfmeE12Cmp00422291@@PAH@Z @0x00423293 (67B):
// __pop_heap result store plus adjust_heap tail; callers 0x004233E9 0x004245D4.
// Evidence: chain lane, callee just landed.
//
// ??$__pop_heap_aux@U?$_Deque_iterator@UBfmeE12@@U?$_Nonconst_traits@UBfmeE12@@@_STL@@@_STL@@UBfmeE12@@UBfmeE12Cmp00422291@@@_STL@@YAXU?$_Deque_iterator@UBfmeE12@@U?$_Nonconst_traits@UBfmeE12@@@_STL@@@0@0PAUBfmeE12@@UBfmeE12Cmp00422291@@@Z @0x00423396 (95B):
// __pop_heap_aux over deque<BfmeE12>; three last-1 operator- calls plus value
// copy feeding rowed __pop_heap. Caller 0x00423A3F.
// Evidence: chain lane, callee just landed.
//
// ??$pop_heap@U?$_Deque_iterator@UBfmeE12@@U?$_Nonconst_traits@UBfmeE12@@@_STL@@@_STL@@UBfmeE12Cmp00422291@@@_STL@@YAXU?$_Deque_iterator@UBfmeE12@@U?$_Nonconst_traits@UBfmeE12@@@_STL@@@0@0UBfmeE12Cmp00422291@@@Z @0x00423A1D (45B):
// pop_heap over deque<BfmeE12> with comparator; copies iterators plus null
// tag feeding rowed __pop_heap_aux. Caller 0x00423F46.
// Evidence: chain lane, callee just landed.
//
// ??$sort_heap@U?$_Deque_iterator@UBfmeE12@@U?$_Nonconst_traits@UBfmeE12@@@_STL@@@_STL@@UBfmeE12Cmp00422291@@@_STL@@YAXU?$_Deque_iterator@UBfmeE12@@U?$_Nonconst_traits@UBfmeE12@@@_STL@@@0@0UBfmeE12Cmp00422291@@@Z @0x00423F20 (67B):
// sort_heap over deque<BfmeE12>; subtract-gated loop of post-decrement plus
// rowed pop_heap. Caller 0x00424612.
// Evidence: chain lane, callee just landed.
#include <algorithm>
#include <deque>
struct BfmeE12 { float x, y, z; };
struct BfmeE12Cmp00422291
{
	__forceinline bool operator()(const BfmeE12 &a, const BfmeE12 &b) const { return a.y < b.y; }
};
template _STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> > _STL::__unguarded_partition<_STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, BfmeE12, BfmeE12Cmp00422291>(_STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, _STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, BfmeE12, BfmeE12Cmp00422291);
template void _STL::__push_heap<_STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, int, BfmeE12, BfmeE12Cmp00422291>(_STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, int, int, BfmeE12, BfmeE12Cmp00422291);
template void _STL::__adjust_heap<_STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, int, BfmeE12, BfmeE12Cmp00422291>(_STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, int, int, BfmeE12, BfmeE12Cmp00422291);
template void _STL::__make_heap<_STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, BfmeE12Cmp00422291, BfmeE12, int>(_STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, _STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, BfmeE12Cmp00422291, BfmeE12 *, int *);
template void _STL::__pop_heap<_STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, BfmeE12, BfmeE12Cmp00422291, int>(_STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, _STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, _STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, BfmeE12, BfmeE12Cmp00422291, int *);
template void _STL::__pop_heap_aux<_STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, BfmeE12, BfmeE12Cmp00422291>(_STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, _STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, BfmeE12 *, BfmeE12Cmp00422291);
template void _STL::pop_heap<_STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, BfmeE12Cmp00422291>(_STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, _STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, BfmeE12Cmp00422291);
template void _STL::sort_heap<_STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, BfmeE12Cmp00422291>(_STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, _STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, BfmeE12Cmp00422291);
