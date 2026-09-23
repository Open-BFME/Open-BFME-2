// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Target copy construction preserves the fixed-storage member operations.
#include "Object872.h"
#include <new>

BfmeObject872Header::BfmeObject872Header(const BfmeObject872Header &other)
{
    memcpy(this, &other, sizeof(*this));
}

namespace _STL {
template<> void _Construct<BfmeObject872, BfmeObject872>(
    BfmeObject872 *dest, const BfmeObject872 &source) throw()
{
    new (dest) BfmeObject872(source);
}
}
