// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ??0Rva0016E3B0@@QAE@HHHH@Z @ 0x0016E3B0 (77B). Four-argument wrapper
// constructor whose only used argument is the hash_map's initial bucket count;
// a non-virtual class with a _STL::hash_map<int, int> member at +0.
// Evidence: SEH frame with handler 0x00B677AB; the four dword stores at
// +4/+8/+0xC/+0x10 are the hashtable bucket vector's three pointers plus
// _M_num_elements, exactly as in the rowed default ctor ??0Rva0016E400; the
// callee at 0x00622410 is the rowed _M_initialize_buckets of the same
// hash_map<int, int> instantiation; no vtable store; ret 0x10 encodes the four
// declared arguments.
// Target bytes are identical to 0x006240E0's except the EH handler immediate
// and the REL32 to _M_initialize_buckets.

// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
#include <vector>
// vector<void*> members kept from this unit's link copies, moved beside <vector> so
// they precede every use. Import-inline: these members are inlined at every use here,
// and this unit's out-of-line copies (referenced from .debug$F alone) are not the ones
// the link keeps.
namespace _STL { template <> void swap<_STLP_alloc_proxy<void **, void *, allocator<void *> > >(_STLP_alloc_proxy<void **, void *, allocator<void *> > &, _STLP_alloc_proxy<void **, void *, allocator<void *> > &); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::_Vector_base(unsigned int, allocator<void *> const &); }
namespace _STL { template <> vector<void *, allocator<void *> >::vector(unsigned int, void *const &, allocator<void *> const &); }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_fill_insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_insert_overflow(void **, void *const &, __true_type const &, unsigned int, bool); }
namespace _STL { template <> void vector<void *, allocator<void *> >::swap(vector<void *, allocator<void *> > &); }
namespace _STL {
template <> __declspec(dllimport) __forceinline _Vector_base<void *, allocator<void *> >::_Vector_base(const allocator<void *> &__a) : _M_start(0), _M_finish(0), _M_end_of_storage(__a, 0) {}
template <> __declspec(dllimport) __forceinline _Vector_base<void *, allocator<void *> >::~_Vector_base() { if (_M_start != 0) _M_end_of_storage.deallocate(_M_start, _M_end_of_storage._M_data - _M_start); }
}
#include <hash_map>
#include <cstddef>
// Import-inline: every __malloc_alloc<0>::deallocate use here is inlined, and this
// unit's out-of-line copy (referenced from .debug$F alone) is not the one the link keeps.
namespace _STL { template <> __declspec(dllimport) __forceinline void _STLP_CALL __malloc_alloc<0>::deallocate(void *__p, size_t) { free((char *)__p); } }
// bfme link decl-only begin
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::capacity() const; }
namespace _STL { template <> allocator<void *> vector<void *, allocator<void *> >::get_allocator() const; }
namespace _STL { template <> void vector<void *, allocator<void *> >::insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::reserve(unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?allocate@?$__malloc_alloc@$0A@@_STL@@SAPAXI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void *__malloc_alloc<0>::allocate(size_t); }
// Suppress this TU's non-retail copy of ?_M_initialize_buckets@?$hashtable@U?$pair@$$CBHH@_STL@@HU?$hash@H@2@U?$_Select1st@U?$pair:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void hashtable<pair<const int, int>, int, hash<int>, _Select1st<pair<const int, int> >, equal_to<int>, allocator<pair<const int, int> > >::_M_initialize_buckets(size_t); }
// Suppress this TU's non-retail copy of ?clear@?$hashtable@U?$pair@$$CBHH@_STL@@HU?$hash@H@2@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void hashtable<pair<const int, int>, int, hash<int>, _Select1st<pair<const int, int> >, equal_to<int>, allocator<pair<const int, int> > >::clear(); }
// Suppress this TU's non-retail copy of ??A?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QBEABQAXI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void *const &vector<void *>::operator[](size_t) const; }
// Suppress this TU's non-retail vector<void*> operator[] copy (family2-LK3 row 25):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void *&_STL::vector<void*>::operator[](size_t);
}
// Suppress this TU's non-retail const-begin copy (row 47 family2-LK3): the
// /Od retail copy in stlport_vector_voidptr.cpp serves the link instead.
namespace _STL {
template <> vector<void *>::const_iterator _STL::vector<void *>::begin() const;
}
// Suppress this TU's non-retail vector<void*> begin/end copies (family2-LK3 rows 6/9):
// the retail copies serve the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> size_t vector<void*>::size() const;
}

class Rva0016E3B0
{
public:
    Rva0016E3B0(int bucketCount, int a, int b, int c);
private:
    _STL::hash_map<int, int> m_map;
};

Rva0016E3B0::Rva0016E3B0(int bucketCount, int a, int b, int c) : m_map(bucketCount) {}

// ??1?$hashtable@U?$pair@$$CBW4NameKeyType@@VDamageFX@@@_STL@@W4NameKeyType@@U?$hash@W4NameKeyType@@@rts@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@VDamageFX@@@_STL@@@2@U?$equal_to@W4NameKeyType@@@5@V?$allocator@U?$pair@$$CBW4NameKeyType@@VDamageFX@@@_STL@@@2@@_STL@@QAE@XZ
// @ 0x0016DEE0 (82B). The DamageFX hash_map's hashtable destructor, inlined
// straight out of the header: ~hashtable() { clear(); } then the bucket
// vector's teardown. Evidence: SEH frame with handler 0x00B677AB (the same TU
// handler as ??0Rva0016E3B0); calls the rowed ?clear@...hashtable 0x0016D610;
// the bucket vector's teardown frees _M_start at +4 through the direct game
// free 0x00030830 (reached, not the msvcr71 import, via /D_CRTIMP= and
// /D_STLP_USE_MALLOC); no vtable store; ret (no stack arguments). /GX, not
// /EHsc, is what keeps the destructor's unwind state.
// The NameKeyType/DamageFX/hash declarations below mirror the real DamageFX.h
// instantiation already recovered in DamageFX_hashtableResize.cpp.

enum NameKeyType
{
    NAMEKEY_INVALID = 0,
    FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

#include "../../../../Include/Common/DamageFXClass.h"
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline pair<NameKeyType const ,DamageFX>::pair(NameKeyType const &a,DamageFX const &b) : first(a), second(b) {} }

namespace rts
{

template<class _Key>
struct hash
{
};

template<>
struct hash<NameKeyType>
{
    unsigned int operator()(const NameKeyType &key) const
    {
        const unsigned int *words = (const unsigned int *)&key;
        return (words[1] << 16) + words[0];
    }
};

template<class _Key>
struct equal_to
{
    bool operator()(const _Key &left, const _Key &right) const
    {
        return left == right;
    }
};

}

// Instantiate only the owned destructor. Whole-map instantiation also emitted
// non-retail resize and range-erase copies that the link selected ahead of
// other units. The destructor still inlines clear and bucket-vector teardown.
typedef _STL::pair<const NameKeyType, DamageFX> DamageFXPair;
typedef _STL::hashtable<DamageFXPair, NameKeyType, rts::hash<NameKeyType>,
    _STL::_Select1st<DamageFXPair>, rts::equal_to<NameKeyType>,
    _STL::allocator<DamageFXPair> > DamageFXTable;
template DamageFXTable::~hashtable();
