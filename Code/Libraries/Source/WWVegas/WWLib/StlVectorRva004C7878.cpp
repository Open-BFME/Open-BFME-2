// Reference: pristine STLport4.5.3. Address-derived opaque record ABI.
// Target boundary and literal pointer stride establish storage width only; no application identity inferred.
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("t", on)
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>



struct Rva004C7878Record { Rva004C7878Record(); Rva004C7878Record(const Rva004C7878Record&); ~Rva004C7878Record(); Rva004C7878Record&operator=(const Rva004C7878Record&); private: char bytes[16]; };
// Retail's helpers call the 45B _Construct at 0x004C734D, rowed under its twin
// element name (StlportConstructFamilyW3G15.cpp): forward to it.
struct Rva004C734DElement;
namespace _STL {
template<> void _Construct<Rva004C734DElement,Rva004C734DElement>(Rva004C734DElement*,const Rva004C734DElement&);
template<> __declspec(dllimport) __forceinline void _Construct<Rva004C7878Record,Rva004C7878Record>(Rva004C7878Record*p,const Rva004C7878Record&v)
{ _Construct(reinterpret_cast<Rva004C734DElement*>(p),reinterpret_cast<const Rva004C734DElement&>(v)); }
}
template void _STL::vector<Rva004C7878Record>::push_back(const Rva004C7878Record&);
