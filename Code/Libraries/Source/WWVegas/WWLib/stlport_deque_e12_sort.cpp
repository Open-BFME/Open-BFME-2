// cl: /O1 /G7 /EHsc /arch:SSE /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// The element type here is a STAND-IN. What the image fixes is the element
// SIZE - it is the stride in every loop and the shift in every distance - and
// a byte-exact body says only that the real element is a POD of that size.
// BfmeE8, BfmeE12 and BfmeE16 name that size and claim nothing more. The
// bodies are byte-exact; the mangled names carry a placeholder where the real
// instantiation's type belongs, and should be repointed if that type is ever
// identified from a call site. The real element's operator< compares the
// float at +4 (the retail compare is a single comiss on that slot).
//
// ??$__unguarded_linear_insert@... @0x00422291 (64B):
// Insertion-sort shift loop over deque<BfmeE12> iterators: backward walk
// with unconditional _M_decrement, 12B element shifts, final value store.
// Evidence: unlock lane, callee _M_decrement rowed, callers 0x00422B4C (76B
// __unguarded_insertion_sort_aux shape) and 0x0042390E, unblocks both.
// ??$sort@... @0x00424D17 (117B), ??$__introsort_loop@... @0x00424AE0 (276B),
// ??$partial_sort@... @0x00424732 (58B), ??$__partial_sort@... @0x0042454E
// (208B) and ??$make_heap@... @0x00423990 (47B): the quicksort half of the
// same family, emitted by the explicit sort instantiation at the end. sort
// calls __introsort_loop then the rowed __final_insertion_sort 0x00424418;
// the loop calls the rowed __unguarded_partition 0x00422217 and partial_sort,
// whose __partial_sort calls make_heap, the rowed __pop_heap 0x00423293 and
// sort_heap 0x00423F20. The loop's __median call lands on 0x005A9215, a body
// with two other callers outside this family (0x0054C083, in a deque<BfmeE8>
// sort, and 0x005A9798): retail folded the medians of those sorts into one
// body. This unit emits it byte-exact, so it is rowed here under this unit's
// instantiation; the other sorts' names belong at the same address.
#include <algorithm>
#include <deque>
struct BfmeE12 { float x, y, z; };
struct BfmeE12Cmp00422291
{
	__forceinline bool operator()(const BfmeE12 &a, const BfmeE12 &b) const { return a.y < b.y; }
};
template void _STL::__unguarded_linear_insert<_STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, BfmeE12, BfmeE12Cmp00422291>(_STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, BfmeE12, BfmeE12Cmp00422291);
template void _STL::__linear_insert<_STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, BfmeE12, BfmeE12Cmp00422291>(_STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, _STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, BfmeE12, BfmeE12Cmp00422291);
template void _STL::__unguarded_insertion_sort_aux<_STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, BfmeE12, BfmeE12Cmp00422291>(_STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, _STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, BfmeE12 *, BfmeE12Cmp00422291);
template void _STL::__insertion_sort<_STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, BfmeE12Cmp00422291>(_STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, _STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, BfmeE12Cmp00422291);
template void _STL::__unguarded_insertion_sort<_STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, BfmeE12Cmp00422291>(_STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, _STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, BfmeE12Cmp00422291);
template void _STL::__final_insertion_sort<_STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, BfmeE12Cmp00422291>(_STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, _STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, BfmeE12Cmp00422291);
template void _STL::sort<_STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, BfmeE12Cmp00422291>(_STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, _STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> >, BfmeE12Cmp00422291);
