// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /G7 /EHsc /MD /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
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
#include <cstddef>
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
// Inline const bucket access without emitting an external specialization.
namespace _STL { template <> __declspec(dllimport) __forceinline void *const &vector<void *>::operator[](size_t n) const { return *(this->_M_start + n); } }
// Inline bucket access without emitting an external vector specialization.
namespace _STL {
template <> __declspec(dllimport) __forceinline void *&_STL::vector<void*>::operator[](size_t n) { return *(this->_M_start + n); }
}
// Inline the bucket start while the shared unit keeps its external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline vector<void *>::const_iterator _STL::vector<void *>::begin() const { return this->_M_start; }
}

// map/set<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); a declaration-only specialization
// stops this TU emitting its copy so callers bind the kept copy.
// Plain (non-dllimport) form: no __imp_ reference is emitted.
namespace _STL {
template <> bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const;
}
// Inline the bucket count while preserving declaration-only mutable iterators.
namespace _STL {
template <> __declspec(dllimport) __forceinline size_t vector<void*>::size() const { return this->_M_finish - this->_M_start; }
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}



#include "ascii_string.h"

// Native pair construction at 29FB63 copies its 52-byte payload through
// 29E067: two AsciiString handles followed by scalar fields. These are the
// accesses of the existing neutral Rva0029E067 provider, not donor field names.
struct Rva002A3FAFRecord {
    Rva002A3FAFRecord();
    __declspec(noinline) Rva002A3FAFRecord(const Rva002A3FAFRecord &);
    ~Rva002A3FAFRecord();
    Rva002A3FAFRecord &operator=(const Rva002A3FAFRecord &);
    AsciiString m_00;
    AsciiString m_04;
    int m_08, m_0c, m_10, m_14, m_18;
    unsigned char m_1c;
    int m_20, m_24, m_28, m_2c, m_30;
    bool operator==(const Rva002A3FAFRecord &) const;
    bool operator<(const Rva002A3FAFRecord &) const;
};

Rva002A3FAFRecord::Rva002A3FAFRecord(const Rva002A3FAFRecord &src)
    : m_00(src.m_00), m_04(src.m_04)
{
    m_08 = src.m_08;
    m_0c = src.m_0c;
    m_10 = src.m_10;
    m_14 = src.m_14;
    m_18 = src.m_18;
    m_1c = src.m_1c;
    m_20 = src.m_20;
    m_24 = src.m_24;
    m_28 = src.m_28;
    m_2c = src.m_2c;
    m_30 = src.m_30;
}


// This caller's native REL32 already names the kept provider at 0x00330E5D.
// Compatible calling convention and argument/return ABI; binding is address-proven.
#pragma comment(linker, "/alternatename:??0Rva002A3FAFRecord@@QAE@XZ=??0RadiusDecalTemplate@@QAE@XZ")

// This caller's native REL32 already names the kept provider at 0x000B6CF1.
// Compatible calling convention and argument/return ABI; binding is address-proven.
#pragma comment(linker, "/alternatename:??1Rva002A3FAFRecord@@QAE@XZ=??1BfmeStringRecord000B94D2@@QAE@XZ")

// Instantiate the recovered member; retain only its required template dependencies.
template Rva002A3FAFRecord & _STL::hash_map<int, Rva002A3FAFRecord, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<int const, Rva002A3FAFRecord> > >::operator[](int const &);
