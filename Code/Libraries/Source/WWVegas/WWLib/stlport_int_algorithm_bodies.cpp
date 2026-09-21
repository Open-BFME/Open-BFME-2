// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Pristine STLport 4.5.3 <algorithm> internals instantiated for int, each
// placed by a single masked whole-.text hit (sort/heap/partition helpers,
// __lower_bound, __median, __gcd, greater<int>). The signed compares fix a
// signed 4-byte element; int stands for any such type folded with it. The
// drivers below only make the compiler emit the helpers and carry no rows.
#include <algorithm>
#include <functional>

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
