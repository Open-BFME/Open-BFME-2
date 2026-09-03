// cl: /O1 /DNDEBUG /MD /EHsc
//
// __lower_bound over const unsigned int* with less<unsigned int>, the
// binary-search worker behind lower_bound on a sorted unsigned array.
//
// Everything about the instantiation is legible in the 57 bytes. sar edx,2
// is the four-byte element stride, so the iterator is a pointer to a 4-byte
// type; sar ecx,1 is arithmetic, so _Distance is signed int and not size_t;
// cmp dword ptr [esi],edi followed by jae is an unsigned compare, which is
// less<unsigned int> and not less<int>; and the value arrives as a pointer
// that is dereferenced once into edi before the loop, which is the const _Tp&
// parameter being hoisted.
//
// The trailing _Distance* parameter carries no value - it exists only to
// hand the distance type to the template - so it is never touched here.
//
// /O1 rather than /O2, and the tell is an absence. At /O2 cl aligns the loop
// head with a seven-byte lea esp,[esp+0] and allocates the hoisted value to
// esi instead of edi; retail has no padding at all and the whole body is
// exactly 57 bytes. Every size-directed level agrees - /O1, /Os and /Oxs all
// reproduce it - so this says the unit was built for size and does not
// distinguish between them.

namespace _STL {

template <class _Tp>
struct less {
	bool operator()(const _Tp& __x, const _Tp& __y) const { return __x < __y; }
};

template <class _RandomAccessIter, class _Distance>
inline void distance(_RandomAccessIter __first, _RandomAccessIter __last, _Distance& __n)
{ __n += __last - __first; }

template <class _RandomAccessIter, class _Distance>
inline void advance(_RandomAccessIter& __i, _Distance __n)
{ __i += __n; }

template <class _ForwardIter, class _Tp, class _Compare, class _Distance>
_ForwardIter __lower_bound(_ForwardIter __first, _ForwardIter __last,
                           const _Tp& __val, _Compare __comp, _Distance*)
{
	_Distance __len = 0;
	distance(__first, __last, __len);
	_Distance __half;
	_ForwardIter __middle;

	while (__len > 0) {
		__half = __len >> 1;
		__middle = __first;
		advance(__middle, __half);
		if (__comp(*__middle, __val)) {
			__first = __middle;
			++__first;
			__len = __len - __half - 1;
		}
		else
			__len = __half;
	}
	return __first;
}

template const unsigned int* __lower_bound<const unsigned int*, unsigned int, less<unsigned int>, int>(
	const unsigned int*, const unsigned int*, const unsigned int&, less<unsigned int>, int*);

}
