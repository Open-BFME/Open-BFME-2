// STLport4.5.3 reference; opaque address-derived record, target stride and container offsets.
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>



struct Rva0037FEA3Record { Rva0037FEA3Record(const Rva0037FEA3Record&); private: char bytes[72]; };
// Retail's copy loop calls the 18B null-guarded construct at 0x0037F71F, rowed
// as Rva0037F71FCopy (Rva0037F551.cpp): forward to it.
class Rva0037F551;
void Rva0037F71FCopy(Rva0037F551 *p, const Rva0037F551 &v);
namespace _STL {template<> __declspec(dllimport) __forceinline void _Construct<Rva0037FEA3Record,Rva0037FEA3Record>(Rva0037FEA3Record*p,const Rva0037FEA3Record&v)
{ Rva0037F71FCopy(reinterpret_cast<Rva0037F551*>(p),reinterpret_cast<const Rva0037F551&>(v)); }}
template void _STL::vector<Rva0037FEA3Record>::reserve(unsigned int);
