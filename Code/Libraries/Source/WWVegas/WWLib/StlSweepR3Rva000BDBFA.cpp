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

#include <list>

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}



struct Rva000BDBFARecord { Rva000BDBFARecord(); Rva000BDBFARecord(const Rva000BDBFARecord&); ~Rva000BDBFARecord(); Rva000BDBFARecord&operator=(const Rva000BDBFARecord&); char bytes[1]; bool operator==(const Rva000BDBFARecord&) const; bool operator<(const Rva000BDBFARecord&) const; };
namespace _STL {template<> void _Construct<Rva000BDBFARecord,Rva000BDBFARecord>(Rva000BDBFARecord*,const Rva000BDBFARecord&);}


// This caller's native REL32 already names the kept provider at 0x000B419E.
// Both declarations use thiscall with one object-pointer/reference argument; binding is address-proven.
#pragma comment(linker, "/alternatename:??4Rva000BDBFARecord@@QAEAAU0@ABU0@@Z=??4Rva000B419E@@QAEAAU0@ABU0@@Z")

// Instantiate the recovered member; retain only its required template dependencies.
template _STL::list<Rva000BDBFARecord, _STL::allocator<Rva000BDBFARecord> > & _STL::list<Rva000BDBFARecord, _STL::allocator<Rva000BDBFARecord> >::operator=(_STL::list<Rva000BDBFARecord, _STL::allocator<Rva000BDBFARecord> > const &);
