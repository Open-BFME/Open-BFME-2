// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport's sort over an array of object pointers, ordered by descending int at
// +0xC of each object: sort (0x002E2D4A, 67B), the introsort loop (0x002E2C79)
// and the partition (0x002E17D6). The rest of the family is rowed by hand in
// Rva002E08A2Insert.cpp and Rva002E1EB7Insert.cpp (median 0x002E0864, inserts,
// heap chain, insertion sorts), and this instantiation reproduces each of
// those bodies byte for byte. The objects are unidentified, so the values stay
// void *, as the hand-written rows have them, and the comparator keeps the
// median's address.
//
// The linear insert calls STLport's __copy_trivial_backward. Retail's copy of
// it (0x00620840) is the one units built for speed emit, with a stack-pointer
// frame and the imported memmove. So its header is compiled with the speed
// option, and _CRTIMP keeps its import default.

#pragma optimize("t", on)
#include <stl/_algobase.h>
#pragma optimize("", on)
#include <algorithm>

struct Rva002E0864Cmp
{
	bool operator()(void *a, void *b) const { return ((const int *)a)[3] > ((const int *)b)[3]; }
};

template void _STL::sort<void **, Rva002E0864Cmp>(void **, void **, Rva002E0864Cmp);
