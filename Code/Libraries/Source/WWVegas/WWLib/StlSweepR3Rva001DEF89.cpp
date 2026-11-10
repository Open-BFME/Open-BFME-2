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


// Retail's helpers reach the element through rowed twins: _Construct 0x001DEDA7 (_Construct<Rva001DF3F1Element>), ~ 0x001DDEC3 (~Rva00414BDBElement) and operator= 0x001DE727 (Rva001DE727::operator=, via the copy dispatch 0x001DE906): forward to them.
struct Rva001DF3F1Element;
struct Rva00414BDBElement { ~Rva00414BDBElement(); };
class Rva001DE727 { public: Rva001DE727&operator=(const Rva001DE727&); };
struct Rva001DEF89Record { Rva001DEF89Record(); Rva001DEF89Record(const Rva001DEF89Record&);
 __declspec(dllimport) __forceinline ~Rva001DEF89Record() { reinterpret_cast<Rva00414BDBElement*>(this)->~Rva00414BDBElement(); }
 __declspec(dllimport) __forceinline Rva001DEF89Record&operator=(const Rva001DEF89Record&x) { reinterpret_cast<Rva001DE727*>(this)->operator=(reinterpret_cast<const Rva001DE727&>(x)); return *this; }
 char bytes[48]; };
namespace _STL {
template<> void _Construct<Rva001DF3F1Element,Rva001DF3F1Element>(Rva001DF3F1Element*,const Rva001DF3F1Element&);
template<> __declspec(dllimport) __forceinline void _Construct<Rva001DEF89Record,Rva001DEF89Record>(Rva001DEF89Record*p,const Rva001DEF89Record&v)
{ _Construct(reinterpret_cast<Rva001DF3F1Element*>(p),reinterpret_cast<const Rva001DF3F1Element&>(v)); }
}


// Instantiate the recovered member; retain only its required template dependencies.
template _STL::vector<Rva001DEF89Record, _STL::allocator<Rva001DEF89Record> > & _STL::vector<Rva001DEF89Record, _STL::allocator<Rva001DEF89Record> >::operator=(_STL::vector<Rva001DEF89Record, _STL::allocator<Rva001DEF89Record> > const &);
