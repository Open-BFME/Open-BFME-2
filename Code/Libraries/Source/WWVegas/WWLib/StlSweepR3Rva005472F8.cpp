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

#include <hash_set>



struct Rva005472F8Record { int word;
// ?Rva005472F8Record::operator< present-unmatched
bool operator<(const Rva005472F8Record&b)const{return word<b.word;}
// ?Rva005472F8Record::operator== present-unmatched
bool operator==(const Rva005472F8Record&b)const{return word==b.word;}
};
namespace _STL {template<>struct __type_traits<Rva005472F8Record>:__type_traits_aux<1>{};}
namespace _STL{template<>struct hash<Rva005472F8Record>{unsigned operator()(const Rva005472F8Record&x)const{return (unsigned)x.word;}};}


// Instantiate the recovered member; retain only its required template dependencies.
template _STL::pair<_STL::_Ht_iterator<Rva005472F8Record, _STL::_Nonconst_traits<Rva005472F8Record>, Rva005472F8Record, _STL::hash<Rva005472F8Record>, _STL::_Identity<Rva005472F8Record>, _STL::equal_to<Rva005472F8Record>, _STL::allocator<Rva005472F8Record> >, bool> _STL::hashtable<Rva005472F8Record, Rva005472F8Record, _STL::hash<Rva005472F8Record>, _STL::_Identity<Rva005472F8Record>, _STL::equal_to<Rva005472F8Record>, _STL::allocator<Rva005472F8Record> >::insert_unique_noresize(Rva005472F8Record const &);
