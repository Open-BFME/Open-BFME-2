// cl: /DNDEBUG /MD /EHsc
//
// binary_search<int*, int> @0x0040AD75 56B: lower_bound through the rowed
// __lower_bound<int*, int, less<int>, int> worker 0x0040AC58, then
// i != last && !(val < *i) with a signed compare. Evidence: sole callee is
// that worker; callers 0x0040AE1F and 0x0040AE51; unique masked hit.
//
// Written out rather than taken from the vendored header, for the same reason
// as stlport_lower_bound_uint.cpp: retail zero-fills the one-byte less<int>
// temporary (xor eax,eax / lea edi,[ebp-4] / stosb) before pushing it, which
// is what value-initialising a POD functor with no base class emits. The
// vendored less derives from binary_function, is not a POD, and leaves the
// slot uninitialised, which drops those bytes and the frame slot.
namespace _STL {

template <class _Tp>
struct less {
	bool operator()(const _Tp& __x, const _Tp& __y) const { return __x < __y; }
};

template <class _ForwardIter, class _Tp, class _Compare, class _Distance>
_ForwardIter __lower_bound(_ForwardIter __first, _ForwardIter __last,
                           const _Tp& __val, _Compare __comp, _Distance*);

// ??$binary_search@PAHH@_STL@@YA_NPAH0ABH@Z @0x0040AD75
template <class _ForwardIter, class _Tp>
bool binary_search(_ForwardIter __first, _ForwardIter __last, const _Tp& __val)
{
	_ForwardIter __i = __lower_bound(__first, __last, __val, less<_Tp>(), (int*)0);
	return __i != __last && !(__val < *__i);
}

template bool binary_search<int*, int>(int*, int*, const int&);

}
