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

#include <hash_map>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline unsigned int vector<void *,allocator<void *> >::size()const  { return (unsigned int)(this->_M_finish - this->_M_start); } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * & vector<void *,allocator<void *> >::operator[](unsigned int n) { return *(this->_M_start + n); } }



struct Rva00057FC1Record { Rva00057FC1Record(); Rva00057FC1Record(const Rva00057FC1Record&); ~Rva00057FC1Record(); Rva00057FC1Record&operator=(const Rva00057FC1Record&); char bytes[1]; bool operator==(const Rva00057FC1Record&) const; bool operator<(const Rva00057FC1Record&) const; };
namespace _STL {template<> void _Construct<Rva00057FC1Record,Rva00057FC1Record>(Rva00057FC1Record*,const Rva00057FC1Record&); template<>struct hash<Rva00057FC1Record> { unsigned int operator()(const Rva00057FC1Record&) const; };}


// Instantiate the recovered member; retain only its required template dependencies.
template void _STL::hashtable<_STL::pair<Rva00057FC1Record const, Rva00057FC1Record>, Rva00057FC1Record, _STL::hash<Rva00057FC1Record>, _STL::_Select1st<_STL::pair<Rva00057FC1Record const, Rva00057FC1Record> >, _STL::equal_to<Rva00057FC1Record>, _STL::allocator<_STL::pair<Rva00057FC1Record const, Rva00057FC1Record> > >::clear(void);

// 0x00058A81 (5B), unreferenced in retail: the out-of-line hash_map::clear
// over the same table, a tail jump into the hashtable clear above.
template void _STL::hash_map<Rva00057FC1Record, Rva00057FC1Record>::clear(void);

// The Record destructor is the pinned name for the 0x00056EB1 body that hashtable::clear calls per node.
#pragma comment(linker, "/alternatename:??1Rva00057FC1Record@@QAE@XZ=?Rva00056EB1Free@@YGXPAX@Z")
