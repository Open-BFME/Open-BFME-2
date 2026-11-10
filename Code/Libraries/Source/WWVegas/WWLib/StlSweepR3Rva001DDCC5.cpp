// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
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
namespace _STL { template <> __declspec(dllimport) __forceinline void * * vector<void *,allocator<void *> >::end() { return this->_M_finish; } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * const * vector<void *,allocator<void *> >::begin()const  { return this->_M_start; } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * * vector<void *,allocator<void *> >::begin() { return this->_M_start; } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * & vector<void *,allocator<void *> >::operator[](unsigned int n) { return *(this->_M_start + n); } }
// bfme link decl-only begin
namespace _STL { template <> void swap<_STLP_alloc_proxy<void **, void *, allocator<void *> > >(_STLP_alloc_proxy<void **, void *, allocator<void *> > &, _STLP_alloc_proxy<void **, void *, allocator<void *> > &); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::_Vector_base(allocator<void *> const &); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::_Vector_base(unsigned int, allocator<void *> const &); }
namespace _STL { template <> vector<void *, allocator<void *> >::vector(allocator<void *> const &); }
namespace _STL { template <> vector<void *, allocator<void *> >::vector(unsigned int, void *const &, allocator<void *> const &); }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_fill_insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_insert_overflow(void **, void *const &, __true_type const &, unsigned int, bool); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_set(void **, void **, void **); }
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::capacity() const; }
namespace _STL { template <> allocator<void *> vector<void *, allocator<void *> >::get_allocator() const; }
namespace _STL { template <> void vector<void *, allocator<void *> >::reserve(unsigned int); }
namespace _STL { template <> void vector<void *, allocator<void *> >::swap(vector<void *, allocator<void *> > &); }
namespace _STL { template <> allocator<void *>::~allocator(); }
// bfme link decl-only end

// map/set<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); a declaration-only specialization
// stops this TU emitting its copy so callers bind the kept copy.
// Plain (non-dllimport) form: no __imp_ reference is emitted.
namespace _STL {
template <> bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const;
}



struct Rva001DDCC5Record {Rva001DDCC5Record();Rva001DDCC5Record(const Rva001DDCC5Record&);~Rva001DDCC5Record();Rva001DDCC5Record&operator=(const Rva001DDCC5Record&);char bytes[1];bool operator<(const Rva001DDCC5Record&)const;bool operator==(const Rva001DDCC5Record&)const;};
namespace _STL {
template void hashtable<pair<const int,Rva001DDCC5Record>,int,hash<int>,_Select1st<pair<const int,Rva001DDCC5Record> >,equal_to<int>,allocator<pair<const int,Rva001DDCC5Record> > >::_M_copy_from(const hashtable<pair<const int,Rva001DDCC5Record>,int,hash<int>,_Select1st<pair<const int,Rva001DDCC5Record> >,equal_to<int>,allocator<pair<const int,Rva001DDCC5Record> > > &);
}

// Retail's _M_new_node is the row at 0x001DD8C9; suppress this TU's own copy (which would call the element copy constructor, defined nowhere) and bind the template name to that row.
namespace _STL { template <> _Hashtable_node<pair<const int,Rva001DDCC5Record> > * hashtable<pair<const int,Rva001DDCC5Record>,int,hash<int>,_Select1st<pair<const int,Rva001DDCC5Record> >,equal_to<int>,allocator<pair<const int,Rva001DDCC5Record> > >::_M_new_node(const pair<const int,Rva001DDCC5Record> &); }
#pragma comment(linker, "/alternatename:?_M_new_node@?$hashtable@U?$pair@$$CBHURva001DDCC5Record@@@_STL@@HU?$hash@H@2@U?$_Select1st@U?$pair@$$CBHURva001DDCC5Record@@@_STL@@@2@U?$equal_to@H@2@V?$allocator@U?$pair@$$CBHURva001DDCC5Record@@@_STL@@@2@@_STL@@AAEPAU?$_Hashtable_node@U?$pair@$$CBHURva001DDCC5Record@@@_STL@@@2@ABU?$pair@$$CBHURva001DDCC5Record@@@2@@Z=?Rva001DD8C9Alloc@@YGPAXABU?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@Z")
