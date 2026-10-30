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
// Keep vector<void*> accessors inline without emitting this unit's COMDAT
// copies: retail's out-of-line ones are the /Od bodies at 0x00023B90-0x00023C20.
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * const * vector<void *,allocator<void *> >::begin()const  { return this->_M_start; } }
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin() { return this->_M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end() { return this->_M_finish; }
template <> __declspec(dllimport) __forceinline
size_t vector<void*>::size() const { return size_t(this->_M_finish - this->_M_start); }
template <> __declspec(dllimport) __forceinline
void *&vector<void*>::operator[](size_t __n) { return *(begin() + __n); }
template <> __declspec(dllimport) __forceinline
void *const &vector<void*>::operator[](size_t __n) const { return *(begin() + __n); }
}



struct Rva005472F8Record { int word;
// ?Rva005472F8Record::operator< present-unmatched
bool operator<(const Rva005472F8Record&b)const{return word<b.word;}
// ?Rva005472F8Record::operator== present-unmatched
bool operator==(const Rva005472F8Record&b)const{return word==b.word;}
};
namespace _STL {template<>struct __type_traits<Rva005472F8Record>:__type_traits_aux<1>{};}
namespace _STL{template<>struct hash<Rva005472F8Record>{unsigned operator()(const Rva005472F8Record&x)const{return (unsigned)x.word;}};}


// Native creation allocates 20 bytes and constructs the full value at +4.
// Keep the member call ABI: retail callers pass the table in ECX.
struct BfmeFloat4Record00469C61;
namespace _STL {
template <> void _Construct<BfmeFloat4Record00469C61, BfmeFloat4Record00469C61>(BfmeFloat4Record00469C61 *, const BfmeFloat4Record00469C61 &);
template <> __declspec(noinline)
_Hashtable_node<Rva005472F8Record> *
hashtable<Rva005472F8Record, Rva005472F8Record, hash<Rva005472F8Record>, _Identity<Rva005472F8Record>, equal_to<Rva005472F8Record>, allocator<Rva005472F8Record> >::_M_new_node(const Rva005472F8Record &value)
{
    char *p = allocator<char>::allocate(20, 0);
    *(int *)p = 0;
    _Construct(reinterpret_cast<BfmeFloat4Record00469C61 *>(p + 4), reinterpret_cast<const BfmeFloat4Record00469C61 &>(value));
    return reinterpret_cast<_Hashtable_node<Rva005472F8Record> *>(p);
}
}

// Instantiate the recovered member; retain only its required template dependencies.
template _STL::pair<_STL::_Ht_iterator<Rva005472F8Record, _STL::_Nonconst_traits<Rva005472F8Record>, Rva005472F8Record, _STL::hash<Rva005472F8Record>, _STL::_Identity<Rva005472F8Record>, _STL::equal_to<Rva005472F8Record>, _STL::allocator<Rva005472F8Record> >, bool> _STL::hashtable<Rva005472F8Record, Rva005472F8Record, _STL::hash<Rva005472F8Record>, _STL::_Identity<Rva005472F8Record>, _STL::equal_to<Rva005472F8Record>, _STL::allocator<Rva005472F8Record> >::insert_unique_noresize(Rva005472F8Record const &);
