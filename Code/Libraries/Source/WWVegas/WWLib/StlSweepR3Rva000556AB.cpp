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

#include <hash_set>
// Keep vector<void*> accessors inline without emitting this unit's COMDAT
// copies: retail's out-of-line ones are the /Od bodies at 0x00023B90-0x00023C20.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin() { return this->_M_start; }
template <> __declspec(dllimport) __forceinline
void *const *vector<void*>::begin() const { return this->_M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end() { return this->_M_finish; }
template <> __declspec(dllimport) __forceinline
size_t vector<void*>::size() const { return size_t(this->_M_finish - this->_M_start); }
template <> __declspec(dllimport) __forceinline
void *&vector<void*>::operator[](size_t __n) { return *(begin() + __n); }
template <> __declspec(dllimport) __forceinline
void *const &vector<void*>::operator[](size_t __n) const { return *(begin() + __n); }
}



struct Rva000556ABRecord { int word;
// ?Rva000556ABRecord::operator< present-unmatched
bool operator<(const Rva000556ABRecord&b)const{return word<b.word;}
// ?Rva000556ABRecord::operator== present-unmatched
bool operator==(const Rva000556ABRecord&b)const{return word==b.word;}
};
namespace _STL {template<>struct __type_traits<Rva000556ABRecord>:__type_traits_aux<1>{};}
namespace _STL{template<>struct hash<Rva000556ABRecord>{unsigned operator()(const Rva000556ABRecord&x)const{return (unsigned)x.word;}};}


// Native creation allocates 12 bytes and constructs the full value at +4.
// Keep the member call ABI: retail callers pass the table in ECX.
class Rva00051C6C;
namespace _STL {
template <> void _Construct<Rva00051C6C, Rva00051C6C>(Rva00051C6C *, const Rva00051C6C &);
template <> __declspec(noinline)
_Hashtable_node<Rva000556ABRecord> *
hashtable<Rva000556ABRecord, Rva000556ABRecord, hash<Rva000556ABRecord>, _Identity<Rva000556ABRecord>, equal_to<Rva000556ABRecord>, allocator<Rva000556ABRecord> >::_M_new_node(const Rva000556ABRecord &value)
{
    char *p = allocator<char>::allocate(12, 0);
    *(int *)p = 0;
    _Construct(reinterpret_cast<Rva00051C6C *>(p + 4), reinterpret_cast<const Rva00051C6C &>(value));
    return reinterpret_cast<_Hashtable_node<Rva000556ABRecord> *>(p);
}
}

// Instantiate the recovered member; retain only its required template dependencies.
template _STL::pair<_STL::_Ht_iterator<Rva000556ABRecord, _STL::_Nonconst_traits<Rva000556ABRecord>, Rva000556ABRecord, _STL::hash<Rva000556ABRecord>, _STL::_Identity<Rva000556ABRecord>, _STL::equal_to<Rva000556ABRecord>, _STL::allocator<Rva000556ABRecord> >, bool> _STL::hashtable<Rva000556ABRecord, Rva000556ABRecord, _STL::hash<Rva000556ABRecord>, _STL::_Identity<Rva000556ABRecord>, _STL::equal_to<Rva000556ABRecord>, _STL::allocator<Rva000556ABRecord> >::insert_unique_noresize(Rva000556ABRecord const &);
