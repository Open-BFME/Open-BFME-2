// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii -Ireference/open-bfme-1/game/GameEngine/Source/Common /Ireference/shims/bfmealloc
// stlport
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

#include <algorithm>

// Retail zero-fills the empty comparator temporary (xor/stosb at 0x00568F5B), which
// value-initialization does only for a less<unsigned int> without the binary_function base.
namespace _STL {
template <>
struct less<unsigned int> {
	__declspec(dllimport) __forceinline bool operator()(const unsigned int &left, const unsigned int &right) const
	{ return left < right; }
};
}

namespace _STL {

template const unsigned int* __lower_bound<const unsigned int*, unsigned int, less<unsigned int>, int>(
	const unsigned int*, const unsigned int*, const unsigned int&, less<unsigned int>, int*);

// lower_bound<const unsigned int*, unsigned int> @0x00568F5B 35B: the public
// wrapper, building the empty less<unsigned int> temporary (xor/stosb into the
// frame slot) and passing a null distance-type pointer to the rowed worker
// 0x00568D2F above. Evidence: sole callee is that worker; unique masked hit.
template const unsigned int* lower_bound<const unsigned int*, unsigned int>(
	const unsigned int*, const unsigned int*, const unsigned int&);

}
