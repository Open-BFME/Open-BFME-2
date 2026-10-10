// cl: /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
#include "Object260.h"
typedef _STL::vector<BfmeFixedObject260, _STL::allocator<BfmeFixedObject260> > BfmeFixedObject260Vector;
template BfmeFixedObject260* BfmeFixedObject260Vector::_M_allocate_and_copy<const BfmeFixedObject260*>(unsigned int, const BfmeFixedObject260*, const BfmeFixedObject260*);

template void BfmeFixedObject260Vector::push_back(const BfmeFixedObject260&);
