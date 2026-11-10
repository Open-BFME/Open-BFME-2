// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}



// Native create_node 0x000BB6CC allocates 0x28: eight link bytes plus
// 32 data bytes, copied through the established 0x000B9478 worker.
struct Rva000BDBFARecord { Rva000BDBFARecord(); Rva000BDBFARecord(const Rva000BDBFARecord&); ~Rva000BDBFARecord(); Rva000BDBFARecord&operator=(const Rva000BDBFARecord&); char bytes[32]; bool operator==(const Rva000BDBFARecord&) const; bool operator<(const Rva000BDBFARecord&) const; };
// Retail's node construction 0x000BB6CC reaches the rowed _Construct<BfmeStringRecord000B75AE>
// 0x000B9478: forward to it.
struct BfmeStringRecord000B75AE;
namespace _STL {
template<> void _Construct<BfmeStringRecord000B75AE,BfmeStringRecord000B75AE>(BfmeStringRecord000B75AE*,const BfmeStringRecord000B75AE&);
template<> __declspec(dllimport) __forceinline void _Construct<Rva000BDBFARecord,Rva000BDBFARecord>(Rva000BDBFARecord*p,const Rva000BDBFARecord&v)
{ _Construct(reinterpret_cast<BfmeStringRecord000B75AE*>(p),reinterpret_cast<const BfmeStringRecord000B75AE&>(v)); }
}


// The native range-erase call at 0x000BDBFA reaches the canonical list erase
// provider at 0x002FECD3. Reuse that provider without emitting cleanup bodies
// for the opaque record. This binds an observed call; it adds no element layout.
class AsciiString;
namespace _STL {
typedef list<AsciiString, allocator<AsciiString> > RetailAsciiList;
template<> RetailAsciiList::iterator RetailAsciiList::erase(RetailAsciiList::iterator, RetailAsciiList::iterator);
template<> __declspec(dllimport) __forceinline
list<Rva000BDBFARecord, allocator<Rva000BDBFARecord> >::iterator
list<Rva000BDBFARecord, allocator<Rva000BDBFARecord> >::erase(iterator first, iterator last)
{
    RetailAsciiList::iterator begin, end;
    begin._M_node = first._M_node;
    end._M_node = last._M_node;
    RetailAsciiList::iterator next = reinterpret_cast<RetailAsciiList *>(this)->erase(begin, end);
    iterator result;
    result._M_node = next._M_node;
    return result;
}
}

// This caller's native REL32 already names the kept provider at 0x000B419E.
// Both declarations use thiscall with one object-pointer/reference argument; binding is address-proven.
#pragma comment(linker, "/alternatename:??4Rva000BDBFARecord@@QAEAAU0@ABU0@@Z=??4Rva000B419E@@QAEAAU0@ABU0@@Z")

// Instantiate the recovered member; retain only its required template dependencies.
template _STL::list<Rva000BDBFARecord, _STL::allocator<Rva000BDBFARecord> > & _STL::list<Rva000BDBFARecord, _STL::allocator<Rva000BDBFARecord> >::operator=(_STL::list<Rva000BDBFARecord, _STL::allocator<Rva000BDBFARecord> > const &);
