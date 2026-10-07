// cl: /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Target copy constructs three sixteen-byte blocks; assignment uses a separate
// member operation. Original type names remain unknown.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

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

// erase is owned by StlportFixedObject60Assign (retail 0x000BC1C2); declare it so this
// unit's clear calls retail's instead of emitting its own copy.
namespace _STL {
template <> BfmeFixedObject60 *vector<BfmeFixedObject60>::erase(BfmeFixedObject60 *, BfmeFixedObject60 *);
}

template BfmeFixedObject60 *_STL::__copy(BfmeFixedObject60 *, BfmeFixedObject60 *, BfmeFixedObject60 *, const random_access_iterator_tag &, int *);
template BfmeFixedObject60 *_STL::__copy_ptrs(BfmeFixedObject60 *, BfmeFixedObject60 *, BfmeFixedObject60 *, _STL::__false_type);
template BfmeFixedObject60 *_STL::__uninitialized_copy(BfmeFixedObject60 *, BfmeFixedObject60 *, BfmeFixedObject60 *, const _STL::__false_type &);
template BfmeFixedObject60 *_STL::__uninitialized_fill_n(BfmeFixedObject60 *, unsigned int, const BfmeFixedObject60 &, const _STL::__false_type &);
template BfmeFixedObject60 *_STL::vector<BfmeFixedObject60, _STL::allocator<BfmeFixedObject60> >::_M_allocate_and_copy<BfmeFixedObject60 *>(unsigned int, BfmeFixedObject60 *, BfmeFixedObject60 *);
template void _STL::vector<BfmeFixedObject60, _STL::allocator<BfmeFixedObject60> >::_M_insert_overflow(BfmeFixedObject60 *, const BfmeFixedObject60 &, const _STL::__false_type &, unsigned int, bool);
template void _STL::vector<BfmeFixedObject60, _STL::allocator<BfmeFixedObject60> >::push_back(const BfmeFixedObject60 &);
template void _STL::vector<BfmeFixedObject60, _STL::allocator<BfmeFixedObject60> >::clear();
