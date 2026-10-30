// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// cl: /O2 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// 0x00627B10 is _STL::push_heap<S4SortElem24 *, S4Cmp009F4BF0>: it forwards
// first, last and the comparator with the two null distance/value type tags
// to __push_heap_aux at 0x006279B0 (stlport_push_heap_s4sortelem24.cpp),
// which copies last[-1] and calls __push_heap 0x00627330. Retail keeps that
// call out of line, so the helper is declared here and not instantiated.
// The partition manager's closest-object query (0x00628040) uses the same
// 24-byte heap element and comparator.
#include <algorithm>

struct S4SortElem24
{
	int m_key;
	int m_values[5];
};

struct S4Cmp009F4BF0
{
public:
	bool operator()(const S4SortElem24 &a, const S4SortElem24 &b) const
	{
		return a.m_key < b.m_key;
	}
};

namespace _STL {
template <> void __push_heap_aux<S4SortElem24 *, S4Cmp009F4BF0, int, S4SortElem24>(
	S4SortElem24 *, S4SortElem24 *, S4Cmp009F4BF0, int *, S4SortElem24 *);
}

template void _STL::push_heap(S4SortElem24 *, S4SortElem24 *, S4Cmp009F4BF0);
