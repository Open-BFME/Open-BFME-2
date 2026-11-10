// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /I. /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <vendor/stlport/stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>


// Retail's helpers reach the element through the rowed 48B element twin
// Rva003F610FElement: _Construct 0x003F5822, ~ 0x003F535B and operator=
// 0x003F554C (via the copy dispatch 0x003F58F8): forward to them.
struct Rva003F610FElement { ~Rva003F610FElement(); Rva003F610FElement&operator=(const Rva003F610FElement&); };
struct Rva003F5FD0Record { Rva003F5FD0Record(); Rva003F5FD0Record(const Rva003F5FD0Record&);
 __declspec(dllimport) __forceinline ~Rva003F5FD0Record() { reinterpret_cast<Rva003F610FElement*>(this)->~Rva003F610FElement(); }
 __declspec(dllimport) __forceinline Rva003F5FD0Record&operator=(const Rva003F5FD0Record&x) { return reinterpret_cast<Rva003F5FD0Record&>(reinterpret_cast<Rva003F610FElement*>(this)->operator=(reinterpret_cast<const Rva003F610FElement&>(x))); }
 char bytes[48]; };
namespace _STL {
template<> void _Construct<Rva003F610FElement,Rva003F610FElement>(Rva003F610FElement*,const Rva003F610FElement&);
template<> __declspec(dllimport) __forceinline void _Construct<Rva003F5FD0Record,Rva003F5FD0Record>(Rva003F5FD0Record*p,const Rva003F5FD0Record&v)
{ _Construct(reinterpret_cast<Rva003F610FElement*>(p),reinterpret_cast<const Rva003F610FElement&>(v)); }
}


// Instantiate the recovered member; retain only its required template dependencies.
template _STL::vector<Rva003F5FD0Record, _STL::allocator<Rva003F5FD0Record> > & _STL::vector<Rva003F5FD0Record, _STL::allocator<Rva003F5FD0Record> >::operator=(_STL::vector<Rva003F5FD0Record, _STL::allocator<Rva003F5FD0Record> > const &);
