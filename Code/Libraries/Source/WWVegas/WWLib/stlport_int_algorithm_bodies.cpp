// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Pristine STLport 4.5.3 <algorithm> internals instantiated for int, each
// placed by a single masked whole-.text hit (sort/heap/partition helpers,
// __lower_bound, __median, __gcd, greater<int>). The signed compares fix a
// signed 4-byte element; int stands for any such type folded with it. The
// drivers below only make the compiler emit the helpers and carry no rows.
#include <algorithm>
#include <functional>

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

void bfmeEmitIntSortHelpers(int *first, int *last)
{
	_STL::sort(first, last);
	_STL::make_heap(first, last);
	_STL::sort_heap(first, last);
	_STL::sort(first, last, _STL::greater<int>());
}

int *bfmeEmitIntLowerBound(int *first, int *last, const int &value)
{
	return _STL::lower_bound(first, last, value);
}

void bfmeEmitIntRotate(int *first, int *middle, int *last)
{
	_STL::rotate(first, middle, last);
}

void bfmeEmitIntPartialSort(int *first, int *last)
{
	_STL::partial_sort(first, last, last, _STL::less<int>());
}

// ??$push_heap@PAHU?$greater@H@_STL@@@_STL@@YAXPAH0U?$greater@H@0@@Z @0x003B02B8 25B
// and ??$__push_heap_aux@PAHU?$greater@H@_STL@@HH@_STL@@YAXPAH0U?$greater@H@0@00@Z
// @0x003B01A0 35B: the push side of the greater<int> heap whose __push_heap
// 0x003B002A is rowed above; push_heap forwards two null type tags to the aux,
// which passes *(last-1), 0 and (last-first)-1. Caller of push_heap 0x003B0448
// (priority_queue<int, vector<int>, greater<int> > push site).
template void _STL::push_heap<int *, _STL::greater<int> >(int *, int *, _STL::greater<int>);
