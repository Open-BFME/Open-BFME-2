// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}



struct Rva001DDBC6Record { char word;
// ?Rva001DDBC6Record::operator< present-unmatched
bool operator<(const Rva001DDBC6Record&b)const{return word<b.word;}
// ?Rva001DDBC6Record::operator== present-unmatched
bool operator==(const Rva001DDBC6Record&b)const{return word==b.word;}
};
namespace _STL {template<>struct __type_traits<Rva001DDBC6Record>:__type_traits_aux<1>{};}
template class _STL::map<int,Rva001DDBC6Record>;
