// cl: /O1 /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>
#include "Object260.h"
typedef _STL::vector<BfmeFixedObject260, _STL::allocator<BfmeFixedObject260> > BfmeFixedObject260Vector;
template BfmeFixedObject260* BfmeFixedObject260Vector::_M_allocate_and_copy<const BfmeFixedObject260*>(unsigned int, const BfmeFixedObject260*, const BfmeFixedObject260*);

template void BfmeFixedObject260Vector::push_back(const BfmeFixedObject260&);
