// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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

#include <list>



struct Rva004677FDRecord { unsigned char bytes[8]; bool operator==(const Rva004677FDRecord&) const; bool operator<(const Rva004677FDRecord&) const; };
// Declared only: retail's element copy is the rowed body at this name's pinned
// address; this TU's copy is not retail's.
namespace _STL { template <> void _Construct<Rva004677FDRecord, Rva004677FDRecord>(Rva004677FDRecord *, const Rva004677FDRecord &); }


// Instantiate the recovered member; retain only its required template dependencies.
// The node's element copy is retail 0x00467763, rowed as ?Rva00467763Construct@@YAXPAXPBX@Z; bind the
// call to that row instead of emitting this unit's own _Construct copy.
void Rva00467763Construct(void *dest, const void *source);
namespace _STL {
// ?_STL::_Construct absent-from-retail
static __forceinline void _Construct(Rva004677FDRecord *dest, const Rva004677FDRecord &source)
{
	Rva00467763Construct(dest, &source);
}
}
template _STL::_List_node<Rva004677FDRecord> * _STL::list<Rva004677FDRecord, _STL::allocator<Rva004677FDRecord> >::_M_create_node(Rva004677FDRecord const &);
