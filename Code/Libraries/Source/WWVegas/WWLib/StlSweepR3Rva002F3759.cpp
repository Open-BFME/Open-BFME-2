// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <map>


template class _STL::map<int,int>;
template class _STL::map<unsigned int,unsigned int>;
template class _STL::map<short,short>;
template class _STL::map<unsigned short,unsigned short>;
template class _STL::map<char,char>;
template class _STL::map<unsigned char,unsigned char>;
template class _STL::map<float,float>;
template class _STL::map<double,double>;
template class _STL::map<void*,void*>;
