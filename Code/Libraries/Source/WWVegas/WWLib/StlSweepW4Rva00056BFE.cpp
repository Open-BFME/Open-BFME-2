// STLport4.5.3 hashtable::resize of MilesAudioManager's request set (hash_set at +0x9C).
// Target evidence: the only caller, 0x00057B27, is that set's insert_unique (it calls
// this body, then insert_unique_noresize at 0x00054BC3), and the bucket helper this body
// calls, 0x00051B89, hashes the key as a pointer (null -> 0, else the dword at +8).
// The row was formerly named as a hash_map<string, element> resize, whose bucket helper
// would call the string hash. Key, hash and equality names are address-derived.
// cl: /O1 /G7 /Oy- /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
#include <vector>
// Keep the visible stateless allocator construction, but emit its shared
// out-of-line copy with the frame-pointer omission used by the kept provider.
namespace _STL {
template <> inline
_STLP_alloc_proxy<void **, void *, allocator<void *> >::_STLP_alloc_proxy(
    const allocator<void *> &a, void **p) : allocator<void *>(a), _M_data(p) {}
}
// vector<void*> members kept from this unit's link copies, moved beside <vector> so
// they precede every use. Import-inline: these members are inlined at every use here,
// and this unit's out-of-line copies (referenced from .debug$F alone) are not the ones
// the link keeps.
namespace _STL { template <> __declspec(dllimport) __forceinline unsigned int vector<void *,allocator<void *> >::size()const  { return (unsigned int)(this->_M_finish - this->_M_start); } }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL {
// The allocator is stateless; only the stored pointers need exchanging.
template <> inline void swap(_STLP_alloc_proxy<void **, void *, allocator<void *> > &left,
                            _STLP_alloc_proxy<void **, void *, allocator<void *> > &right)
{
    swap(left._M_data, right._M_data);
}
}

namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::_STLP_alloc_proxy(const _STLP_alloc_proxy<void **, void *, allocator<void *> > &); }
namespace _STL {
template <> __declspec(dllimport) __forceinline _Vector_base<void *, allocator<void *> >::~_Vector_base() { if (_M_start != 0) _M_end_of_storage.deallocate(_M_start, _M_end_of_storage._M_data - _M_start); }
}
#include <hash_set>

// Layout view of MilesAudioManager.cpp's request record: only +0x08 is read here.
struct Rva00051107AudioRequest { int m_request; char m_at04[4]; unsigned int m_at08; char m_at0C[0x18 - 0x0C]; };
struct Rva00051B89Hash {
    unsigned int operator()(const Rva00051107AudioRequest *req) const
    {
        unsigned int handle = reinterpret_cast<unsigned int>(req);
        if (req)
            handle = req->m_at08;
        return handle;
    }
};
struct Rva00050E1CEqualTo {
    bool operator()(const Rva00051107AudioRequest *left, const Rva00051107AudioRequest *right) const;
};

typedef _STL::hashtable<Rva00051107AudioRequest *, Rva00051107AudioRequest *, Rva00051B89Hash,
    _STL::_Identity<Rva00051107AudioRequest *>, Rva00050E1CEqualTo,
    _STL::allocator<Rva00051107AudioRequest *> > Rva00051107AudioRequestTable;

// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * & vector<void *,allocator<void *> >::operator[](unsigned int n) { return *(this->_M_start + n); } }
// bfme link decl-only begin
namespace _STL { template <> allocator<void *> vector<void *, allocator<void *> >::get_allocator() const; }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??$__less@I@_STL@@YA?AU?$less@I@0@PAI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> less<unsigned int> __less<unsigned int>(unsigned int *); }
// map/set<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); a declaration-only specialization
// stops this TU emitting its copy so callers bind the kept copy.
// Plain (non-dllimport) form: no __imp_ reference is emitted.
namespace _STL {
template <> bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const;
}

// Instantiate the recovered operation and its required template dependencies.
template void Rva00051107AudioRequestTable::resize(unsigned int);
