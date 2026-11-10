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


// Retail's helpers reach the element through rowed twins: _Construct 0x001FF819 (_Construct<vector<ScienceType> >), ~ 0x0007FAB3 (~vector<int>) and operator= 0x0021C21B (vector<Rva0021C21BElement>::operator=, via the copy dispatch 0x00339A8D): forward to them.
enum ScienceType;
struct Rva0021C21BElement;
namespace _STL {
template<> vector<int, allocator<int> >::~vector();
template<> vector<Rva0021C21BElement, allocator<Rva0021C21BElement> > &vector<Rva0021C21BElement, allocator<Rva0021C21BElement> >::operator=(const vector<Rva0021C21BElement, allocator<Rva0021C21BElement> >&);
}
struct Rva001FFD6BRecord { Rva001FFD6BRecord(); Rva001FFD6BRecord(const Rva001FFD6BRecord&);
 __declspec(dllimport) __forceinline ~Rva001FFD6BRecord() { reinterpret_cast<_STL::vector<int, _STL::allocator<int> >*>(this)->~vector(); }
 __declspec(dllimport) __forceinline Rva001FFD6BRecord&operator=(const Rva001FFD6BRecord&x) { typedef _STL::vector<Rva0021C21BElement, _STL::allocator<Rva0021C21BElement> > V; reinterpret_cast<V*>(this)->operator=(reinterpret_cast<const V&>(x)); return *this; }
 char bytes[12]; };
namespace _STL {
template<> void _Construct<_STL::vector<ScienceType, _STL::allocator<ScienceType> >,_STL::vector<ScienceType, _STL::allocator<ScienceType> > >(_STL::vector<ScienceType, _STL::allocator<ScienceType> >*,const _STL::vector<ScienceType, _STL::allocator<ScienceType> >&);
template<> __declspec(dllimport) __forceinline void _Construct<Rva001FFD6BRecord,Rva001FFD6BRecord>(Rva001FFD6BRecord*p,const Rva001FFD6BRecord&v)
{ _Construct(reinterpret_cast<_STL::vector<ScienceType, _STL::allocator<ScienceType> >*>(p),reinterpret_cast<const _STL::vector<ScienceType, _STL::allocator<ScienceType> >&>(v)); }
}


// Instantiate the recovered member; retain only its required template dependencies.
template _STL::vector<Rva001FFD6BRecord, _STL::allocator<Rva001FFD6BRecord> > & _STL::vector<Rva001FFD6BRecord, _STL::allocator<Rva001FFD6BRecord> >::operator=(_STL::vector<Rva001FFD6BRecord, _STL::allocator<Rva001FFD6BRecord> > const &);
