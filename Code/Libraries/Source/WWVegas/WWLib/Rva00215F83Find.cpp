// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??$__find@PAUBfmePod28@@H@_STL@@YAPAUBfmePod28@@PAU1@0HABUrandom_access_iterator_tag@0@@Z @0x00215F83 108B
// Unrolled random-access __find over 28-byte elements comparing a[0] against an
// int key passed by value (retail loads the key once into esi and compares the
// element's first dword directly). Trip count is the element count shifted by
// two, then a remainder switch, as in the 20/40/104-byte siblings in
// stlport_pod_vector_bodies.cpp. Element view only; no record meaning claimed.
#include <stl/_algobase.h>
struct BfmePod28 { int a[7]; };
inline bool operator==(const BfmePod28 &x, int v) { return x.a[0] == v; }
namespace _STL {
template <class It, class T>
It __find(It first, It last, T val, const random_access_iterator_tag &)
{
	int trip = (int)(last - first) >> 2;
	for (; trip > 0; --trip) {
		if (*first == val) return first; ++first;
		if (*first == val) return first; ++first;
		if (*first == val) return first; ++first;
		if (*first == val) return first; ++first;
	}
	switch (last - first) {
	case 3: if (*first == val) return first; ++first;
	case 2: if (*first == val) return first; ++first;
	case 1: if (*first == val) return first; ++first;
	default: return last;
	}
}
}
template BfmePod28* _STL::__find(BfmePod28*, BfmePod28*, int, const _STL::random_access_iterator_tag&);
