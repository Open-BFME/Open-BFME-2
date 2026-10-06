// cl: /O1 /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Target copy constructs three sixteen-byte blocks; assignment uses a separate
// member operation. Original type names remain unknown.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>
struct BfmeFixedBlock16 { unsigned int words[4]; BfmeFixedBlock16(); };
struct BfmeFixedObject60 {
 unsigned int word_00,word_04,word_08;
 BfmeFixedBlock16 blocks_0C[3];
 BfmeFixedObject60();
 BfmeFixedObject60(const BfmeFixedObject60& rhs);
 BfmeFixedObject60& operator=(const BfmeFixedObject60& rhs);
};
typedef char FixedObjectExtent[sizeof(BfmeFixedObject60) == 60 ? 1 : -1];

template BfmeFixedObject60 *_STL::__copy(BfmeFixedObject60 *, BfmeFixedObject60 *, BfmeFixedObject60 *, const random_access_iterator_tag &, int *);
template BfmeFixedObject60 *_STL::__copy_ptrs(BfmeFixedObject60 *, BfmeFixedObject60 *, BfmeFixedObject60 *, _STL::__false_type);
template BfmeFixedObject60 *_STL::__uninitialized_copy(BfmeFixedObject60 *, BfmeFixedObject60 *, BfmeFixedObject60 *, const _STL::__false_type &);
template BfmeFixedObject60 *_STL::__uninitialized_fill_n(BfmeFixedObject60 *, unsigned int, const BfmeFixedObject60 &, const _STL::__false_type &);
template BfmeFixedObject60 *_STL::vector<BfmeFixedObject60, _STL::allocator<BfmeFixedObject60> >::_M_allocate_and_copy<BfmeFixedObject60 *>(unsigned int, BfmeFixedObject60 *, BfmeFixedObject60 *);
template void _STL::vector<BfmeFixedObject60, _STL::allocator<BfmeFixedObject60> >::_M_insert_overflow(BfmeFixedObject60 *, const BfmeFixedObject60 &, const _STL::__false_type &, unsigned int, bool);
template void _STL::vector<BfmeFixedObject60, _STL::allocator<BfmeFixedObject60> >::push_back(const BfmeFixedObject60 &);
template void _STL::vector<BfmeFixedObject60, _STL::allocator<BfmeFixedObject60> >::clear();
