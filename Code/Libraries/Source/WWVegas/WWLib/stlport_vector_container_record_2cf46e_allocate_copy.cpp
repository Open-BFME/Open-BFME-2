// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// BFME2's 12-byte BfmeContainerRecord002CF46E vector allocation/copy helper at RVA 0x2CFBF4.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../../GameEngine/Include/Common/BfmeFixedStorage002CF0F0.h"
#include <vector>
struct BfmeContainerRecord002CF46E {
    BfmeFixedStorage002CF0F0 storage;
    AsciiString text;
    unsigned int word8;
    BfmeContainerRecord002CF46E();
    BfmeContainerRecord002CF46E(const BfmeContainerRecord002CF46E &);
};
namespace _STL {
template <> void _Construct<BfmeContainerRecord002CF46E, BfmeContainerRecord002CF46E>(BfmeContainerRecord002CF46E *, const BfmeContainerRecord002CF46E &);
}
// Only the rowed members: a whole-class instantiation also emitted this
// TU's operator=, which differs from retail and, first in link order, was
// kept over stlport_vector_container_record_2cf46e_assign.cpp's copy.
typedef _STL::vector<BfmeContainerRecord002CF46E, _STL::allocator<BfmeContainerRecord002CF46E> > BfmeContainerRecord002CF46EVector;
template void BfmeContainerRecord002CF46EVector::push_back(const BfmeContainerRecord002CF46E &);
template BfmeContainerRecord002CF46E *BfmeContainerRecord002CF46EVector::_M_allocate_and_copy<const BfmeContainerRecord002CF46E *>(unsigned int, const BfmeContainerRecord002CF46E *, const BfmeContainerRecord002CF46E *);
