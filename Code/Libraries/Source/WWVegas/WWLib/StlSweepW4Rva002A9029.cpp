// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /Og /Os /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
#include "ascii_string.h"
#include <hash_map>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline unsigned int vector<void *,allocator<void *> >::size()const  { return (unsigned int)(this->_M_finish - this->_M_start); } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * & vector<void *,allocator<void *> >::operator[](unsigned int n) { return *(this->_M_start + n); } }
// bfme link decl-only begin
namespace _STL { template <> void swap<_STLP_alloc_proxy<void **, void *, allocator<void *> > >(_STLP_alloc_proxy<void **, void *, allocator<void *> > &, _STLP_alloc_proxy<void **, void *, allocator<void *> > &); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::_Vector_base(unsigned int, allocator<void *> const &); }
namespace _STL { template <> vector<void *, allocator<void *> >::vector(unsigned int, void *const &, allocator<void *> const &); }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> allocator<void *> vector<void *, allocator<void *> >::get_allocator() const; }
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

// The mapped value of retail's hash_map<int, AsciiString> (row 0x00523DB7 builds this pair), so a node copy-constructs the string.
struct Rva002A9029Element { AsciiString value; bool operator<(const Rva002A9029Element&)const; bool operator==(const Rva002A9029Element&)const; };
namespace _STL {template<> struct hash<Rva002A9029Element> { unsigned operator()(const Rva002A9029Element&) const; };}
// resize is retail's shared 0x0053F1EC body (pinned); declare it so this TU binds that copy.
namespace _STL { template <> void hashtable<pair<int const, Rva002A9029Element>, int, hash<int>, _Select1st<pair<int const, Rva002A9029Element> >, equal_to<int>, allocator<pair<int const, Rva002A9029Element> > >::resize(unsigned int); }

// Instantiate the recovered operation and its required template dependencies.
template _STL::pair<int const, Rva002A9029Element> & _STL::hashtable<_STL::pair<int const, Rva002A9029Element>, int, _STL::hash<int>, _STL::_Select1st<_STL::pair<int const, Rva002A9029Element> >, _STL::equal_to<int>, _STL::allocator<_STL::pair<int const, Rva002A9029Element> > >::_M_insert(_STL::pair<int const, Rva002A9029Element> const &);
