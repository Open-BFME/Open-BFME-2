// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// ??0Rva006240E0@@QAE@HHHH@Z @ 0x006240E0 (77B). Four-argument wrapper
// constructor whose only used argument is the hash_map's initial bucket count;
// a non-virtual class with a _STL::hash_map<int, int> member at +0.
// Evidence: SEH frame with handler 0x00BA74FB; the four dword stores at
// +4/+8/+0xC/+0x10 are the hashtable bucket vector's three pointers plus
// _M_num_elements, exactly as in the rowed default ctor ??0Rva0016E400; the
// callee at 0x00622410 is the rowed _M_initialize_buckets of the same
// hash_map<int, int> instantiation; no vtable store; ret 0x10 encodes the four
// declared arguments.
// Target bytes are identical to 0x0016E3B0's except the EH handler immediate
// and the REL32 to _M_initialize_buckets.

// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
#include <vector>
// vector<void*> members kept from this unit's link copies, moved beside <vector> so
// they precede every use. Import-inline: these members are inlined at every use here,
// and this unit's out-of-line copies (referenced from .debug$F alone) are not the ones
// the link keeps.
namespace _STL { template <> __declspec(dllimport) __forceinline allocator<void *>::~allocator() {} }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_fill_insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_insert_overflow(void **, void *const &, __true_type const &, unsigned int, bool); }
namespace _STL {
template <> __declspec(dllimport) __forceinline _Vector_base<void *, allocator<void *> >::_Vector_base(const allocator<void *> &__a) : _M_start(0), _M_finish(0), _M_end_of_storage(__a, 0) {}
}
#include <hash_map>
#include <cstddef>
// Bind to the kept retail copy instead of emitting this unit's own.
// bfme link decl-only begin
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::capacity() const; }
namespace _STL { template <> void vector<void *, allocator<void *> >::insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::reserve(unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??1?$hashtable@U?$pair@$$CBHH@_STL@@HU?$hash@H@2@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2@U?$:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> hashtable<pair<const int, int>, int, hash<int>, _Select1st<pair<const int, int> >, equal_to<int>, allocator<pair<const int, int> > >::~hashtable(); }
// Suppress this TU's non-retail copy of ?_M_initialize_buckets@?$hashtable@U?$pair@$$CBHH@_STL@@HU?$hash@H@2@U?$_Select1st@U?$pair:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void hashtable<pair<const int, int>, int, hash<int>, _Select1st<pair<const int, int> >, equal_to<int>, allocator<pair<const int, int> > >::_M_initialize_buckets(size_t); }
// Suppress this TU's non-retail copy of ?clear@?$hashtable@U?$pair@$$CBHH@_STL@@HU?$hash@H@2@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void hashtable<pair<const int, int>, int, hash<int>, _Select1st<pair<const int, int> >, equal_to<int>, allocator<pair<const int, int> > >::clear(); }
// Suppress this TU's non-retail vector<void*> operator[] copy (family2-LK3 row 25):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void *&_STL::vector<void*>::operator[](size_t);
}
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> size_t vector<void*>::size() const;
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}

class Rva006240E0
{
public:
    Rva006240E0(int bucketCount, int a, int b, int c);
private:
    _STL::hash_map<int, int> m_map;
};

Rva006240E0::Rva006240E0(int bucketCount, int a, int b, int c) : m_map(bucketCount) {}
