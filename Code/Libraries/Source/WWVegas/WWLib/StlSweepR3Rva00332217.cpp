// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /Ivendor /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stlport/stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>


// Retail's helpers reach the element through rowed twins: _Construct 0x00331B3D (_Construct<BfmeStringRecord00331962>), ~ 0x0029D7C2 (~Rva00286297) and operator= 0x00331759 (the copy-ctor-folded body rowed as Rva002DFC30(const&), via the copy dispatch 0x003319C9): forward to them.
struct BfmeStringRecord00331962;
struct Rva00286297 { ~Rva00286297(); };
class Rva002DFC30 { public: Rva002DFC30(const Rva002DFC30&); };
struct Rva00332217Record { Rva00332217Record(); Rva00332217Record(const Rva00332217Record&);
 __declspec(dllimport) __forceinline ~Rva00332217Record() { reinterpret_cast<Rva00286297*>(this)->~Rva00286297(); }
 __declspec(dllimport) __forceinline Rva00332217Record&operator=(const Rva00332217Record&x) { reinterpret_cast<Rva002DFC30*>(this)->Rva002DFC30::Rva002DFC30(reinterpret_cast<const Rva002DFC30&>(x)); return *this; }
 char bytes[12]; };
namespace _STL {
template<> void _Construct<BfmeStringRecord00331962,BfmeStringRecord00331962>(BfmeStringRecord00331962*,const BfmeStringRecord00331962&);
template<> __declspec(dllimport) __forceinline void _Construct<Rva00332217Record,Rva00332217Record>(Rva00332217Record*p,const Rva00332217Record&v)
{ _Construct(reinterpret_cast<BfmeStringRecord00331962*>(p),reinterpret_cast<const BfmeStringRecord00331962&>(v)); }
}


// Instantiate the recovered member; retain only its required template dependencies.
template _STL::vector<Rva00332217Record, _STL::allocator<Rva00332217Record> > & _STL::vector<Rva00332217Record, _STL::allocator<Rva00332217Record> >::operator=(_STL::vector<Rva00332217Record, _STL::allocator<Rva00332217Record> > const &);
