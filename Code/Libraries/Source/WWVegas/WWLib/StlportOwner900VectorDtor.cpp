// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Target vector<Owner900> dtor at 0x004CB996/63 and _M_clear at 0x004CB9D5/30 via rowed _Destroy 0x004CB97E and _free 0x30830.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include "OwnedRecord900.h"
template _STL::vector<BfmeRecordOwner900, _STL::allocator<BfmeRecordOwner900> >::~vector();
template void _STL::vector<BfmeRecordOwner900, _STL::allocator<BfmeRecordOwner900> >::_M_clear();
