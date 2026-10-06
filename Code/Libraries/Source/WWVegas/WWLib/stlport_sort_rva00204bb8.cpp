// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// STLport sort<int*, Rva00204BB8> and its insertion-sort half over int sort
// keys with the rowed thiscall comparator Rva00204BB8 (0x00204BB8):
//   sort                           0x0020CE84  67B
//   __final_insertion_sort         0x00207B4C  68B
//   __insertion_sort               0x00207490  45B
//   __unguarded_insertion_sort     0x002074BD  23B
//   __unguarded_insertion_sort_aux 0x00206D12  33B
//   __linear_insert                0x00206CD3  63B
//   __unguarded_linear_insert      0x002059A0  47B
//   __unguarded_partition          0x00205840  73B
// Evidence: each places uniquely by masked search in 0x204B00-0x20D000 (the
// 23B __unguarded_insertion_sort splits from the rowed 23B pop_heap wrapper
// 0x00207BC3 by its callee 0x00206D12); sort calls the introsort loop
// 0x0020C04C (stlport_median_rva00204bb8.cpp) and __final_insertion_sort; the
// leaves call the rowed comparator and __copy_trivial_backward 0x00620840.
// Unlike the Rva00422CA8 and Rva00568721 families, every body here is the
// vendored header's: the plain __unguarded_linear_insert, no loaded
// temporary. The heap half is rowed in the per-member rva00204bb8 units.
#include <algorithm>

class Rva00204BB8
{
public:
	bool operator()(int a, int b) const;
};

// ??$sort@PAHVRva00204BB8@@@_STL@@YAXPAH0VRva00204BB8@@@Z @0x0020CE84 and its callees
template void _STL::sort<int *, Rva00204BB8>(int *, int *, Rva00204BB8);
