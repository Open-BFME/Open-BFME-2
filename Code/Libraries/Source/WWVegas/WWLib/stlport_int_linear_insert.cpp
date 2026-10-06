// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??$__linear_insert@PAHHU?$less@H@_STL@@@_STL@@YAXPAH0HU?$less@H@0@@Z
// retail 0x0040AE5E, 52 bytes. Guarded int insert with less<int>.
// Evidence: pin address read from REL32 at +0x1a of body at 0x0040B247;
// caller __insertion_sort at 0x0040B260; callees copy_backward ObjectID
// rowed at 0x005E42D3 and __unguarded_linear_insert int rowed at 0x0040A77B;
// neighbours pop_heap 0x0040ADC6 and sort_heap 0x0040AE92 share these flags
// in stlport_int_introsort_loop.cpp. Vendored 4.5.3 would inline
// copy_backward<int> to __copy_trivial_backward; retail 4.6-style keeps the
// typed ObjectID wrapper call, so select that helper via ObjectID casts.
#include <functional>

enum ObjectID { INVALID_ID = 0 };

namespace _STL
{

template <class _InputIter, class _OutputIter>
_OutputIter copy_backward(_InputIter __first, _InputIter __last,
	_OutputIter __result);

template <class _RandomAccessIter, class _Tp, class _Compare>
void __unguarded_linear_insert(_RandomAccessIter __last, _Tp __val,
	_Compare __comp);

template <class _RandomAccessIter, class _Tp, class _Compare>
void __linear_insert(_RandomAccessIter __first, _RandomAccessIter __last,
	_Tp __val, _Compare __comp)
{
	if (__comp(__val, *__first))
	{
		copy_backward((ObjectID *)__first, (ObjectID *)__last,
			(ObjectID *)(__last + 1));
		*__first = __val;
	}
	else
	{
		__unguarded_linear_insert(__last, __val, __comp);
	}
}

template void __linear_insert<int *, int, _STL::less<int> >(int *, int *,
	int, _STL::less<int>);

}
