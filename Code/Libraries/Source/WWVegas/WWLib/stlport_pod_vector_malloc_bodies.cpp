// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// Pristine STLport 4.5.3 vector members for placeholder POD elements, in the
// _STLP_USE_MALLOC allocator configuration. Each body was placed by a single
// masked whole-.text hit and its own bytes carry the element stride.
// BfmePodN stands for the real N-byte element at each site; where retail's
// copy construct for it is non-trivial, _Construct<BfmePodN> is pinned by
// call-site address, not compiled here. No retail caller is claimed. The
// 8/12/16-byte callees resolve to the existing BfmeE8/E12/E16 rows, the same
// placeholder sizes under their older names.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
// These elements copy through real copy constructors; their _Construct
// bodies are rowed under the real element names, so call those.
struct BfmePod16;
struct BfmeNarrowRecord0041A617;
struct BfmePod8;
void __cdecl Rva004C3A9FConstruct(void *, const void *);
namespace _STL {
template <> void _Construct<BfmeNarrowRecord0041A617, BfmeNarrowRecord0041A617>(BfmeNarrowRecord0041A617 *, const BfmeNarrowRecord0041A617 &);
// 0x0041A727
template <> __declspec(dllimport) __forceinline void _Construct<BfmePod16, BfmePod16>(BfmePod16 *p, const BfmePod16 &v)
{ _Construct((BfmeNarrowRecord0041A617 *)p, (const BfmeNarrowRecord0041A617 &)v); }
// 0x004C3A9F
template <> __declspec(dllimport) __forceinline void _Construct<BfmePod8, BfmePod8>(BfmePod8 *p, const BfmePod8 &v)
{ ::Rva004C3A9FConstruct(p, &v); }
}
// Suppress this TU's non-retail copy of ?erase@?$vector@UBfmePod12@@V?$allocator@UBfmePod12@@@_STL@@@_STL@@QAEPAUBfmePod12@@PAU3@0:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod12;
namespace _STL { template <> BfmePod12 * vector<BfmePod12,allocator<BfmePod12> >::erase(BfmePod12 *,BfmePod12 *); }
// Suppress this TU's non-retail copy of ?allocate@?$allocator@UBfmePod40@@@_STL@@QBEPAUBfmePod40@@IPBX@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod40;
namespace _STL { template <> BfmePod40 * allocator<BfmePod40>::allocate(unsigned int,void const *) const; }
// Suppress this TU's non-retail copy of ?allocate@?$allocator@UBfmePod68@@@_STL@@QBEPAUBfmePod68@@IPBX@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod68;
namespace _STL { template <> BfmePod68 * allocator<BfmePod68>::allocate(unsigned int,void const *) const; }
// Suppress this TU's non-retail copy of ?_M_insert_overflow@?$vector@UBfmePod68@@V?$allocator@UBfmePod68@@@_STL@@@_STL@@IAEXPAUBfm:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void vector<BfmePod68,allocator<BfmePod68> >::_M_insert_overflow(BfmePod68 *,BfmePod68 const &,__false_type const &,unsigned int,bool); }
// Suppress this TU's non-retail copy of ?allocate@?$allocator@UBfmePod16@@@_STL@@QBEPAUBfmePod16@@IPBX@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> BfmePod16 * allocator<BfmePod16>::allocate(unsigned int,void const *) const; }
// Suppress this TU's non-retail copy of ?resize@?$vector@UBfmePod44@@V?$allocator@UBfmePod44@@@_STL@@@_STL@@QAEXI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod44;
namespace _STL { template <> void vector<BfmePod44, allocator<BfmePod44> >::resize(size_t); }
// Suppress this TU's non-retail copy of ?allocate@?$allocator@UBfmePod8@@@_STL@@QBEPAUBfmePod8@@IPBX@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> BfmePod8 *allocator<BfmePod8>::allocate(size_t, const void *) const; }

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}
struct BfmePod8 { int a[2]; };
// allocator<BfmePod8>::allocate is kept from the bfmealloc pod units (retail's
// 0x00523D6C fold); declare it so this malloc-configured unit emits no copy.
namespace _STL { template <> BfmePod8 *allocator<BfmePod8>::allocate(size_t, const void *) const; }
struct BfmePod12 { int a[3]; };
struct BfmePod16 { int a[4]; };
struct BfmePod40 { int a[10]; };
// The 0x0054014D forwarder calls the rowed 40-byte nontrivial copy worker
// at 0x00540082, the camera-track key Rva0054000B's copy. Keep its record name
// instead of emitting a raw-int copy.
class Rva0054000B;
namespace _STL {
template <> Rva0054000B *__copy<Rva0054000B *, Rva0054000B *, int>(Rva0054000B *, Rva0054000B *, Rva0054000B *, const random_access_iterator_tag &, int *);
template <> __declspec(dllimport) __forceinline BfmePod40 *__copy<BfmePod40 *, BfmePod40 *, int>(BfmePod40 *first, BfmePod40 *last, BfmePod40 *result, const random_access_iterator_tag &tag, int *distance)
{ return (BfmePod40 *)__copy((Rva0054000B *)first, (Rva0054000B *)last, (Rva0054000B *)result, tag, distance); }
}
// bfme link decl-only BfmePod40
namespace _STL { template <> vector<BfmePod40, allocator<BfmePod40> >::~vector(); }
struct BfmePod44 { int a[11]; };
// Retail 81AF2 is STLport's no-EH overflow path, also used by the 82819 fill.
// Reference: vendor/stlport/stl/_vector.h (STLport 4.5.3); the retail body
// has no unwind path although this unit otherwise enables exceptions.
// Keep that path visible so the unused empty tag does not change the caller.
namespace _STL {
template <> BfmePod44 *allocator<BfmePod44>::allocate(size_t, const void *) const;
template <> inline void vector<BfmePod44>::_M_insert_overflow(BfmePod44 *position, const BfmePod44 &value, const __false_type &, size_t count, bool atEnd)
{
    const size_t oldSize = size();
    const size_t length = oldSize + (max)(oldSize, count);
    BfmePod44 *newStart = this->_M_end_of_storage.allocate(length);
    BfmePod44 *newFinish = newStart;
    newFinish = __uninitialized_copy(this->_M_start, position, newStart, __false_type());
    if (count == 1) {
        _Construct(newFinish, value);
        ++newFinish;
    } else
        newFinish = __uninitialized_fill_n(newFinish, count, value, __false_type());
    if (!atEnd)
        newFinish = __uninitialized_copy(position, this->_M_finish, newFinish, __false_type());
    _M_clear();
    _M_set(newStart, newFinish, newStart + length);
}
}
struct BfmePod68 { int a[17]; };

// MilesAudioManager's 8-byte trigger-area records: retail folds their erase
// onto the BfmePod8 body (0x003FA4DB, called twice by 0x000587C6).
struct AudioTriggerArea { int a[2]; };
struct AudioTriggerAreaSave { int a[2]; };

// Instantiate the matched members without unrelated container operations.
template void _STL::vector<BfmePod44,_STL::allocator<BfmePod44> >::_M_fill_insert(BfmePod44 *,unsigned int,BfmePod44 const &);



template BfmePod12 * _STL::vector<BfmePod12,_STL::allocator<BfmePod12> >::erase(BfmePod12 *);

template BfmePod16 * _STL::vector<BfmePod16,_STL::allocator<BfmePod16> >::erase(BfmePod16 *);


template BfmePod68 * _STL::vector<BfmePod68,_STL::allocator<BfmePod68> >::erase(BfmePod68 *);



template BfmePod68 * _STL::__copy_ptrs<BfmePod68 *,BfmePod68 *>(BfmePod68 *,BfmePod68 *,BfmePod68 *,_STL::__false_type const &);


template BfmePod16 * _STL::vector<BfmePod16,_STL::allocator<BfmePod16> >::erase(BfmePod16 *,BfmePod16 *);


template BfmePod44 * _STL::vector<BfmePod44,_STL::allocator<BfmePod44> >::erase(BfmePod44 *,BfmePod44 *);


template void _STL::vector<BfmePod16,_STL::allocator<BfmePod16> >::clear(void);


template void _STL::vector<BfmePod12,_STL::allocator<BfmePod12> >::clear(void);

template void _STL::vector<BfmePod44,_STL::allocator<BfmePod44> >::insert(BfmePod44 *,unsigned int,BfmePod44 const &);

template AudioTriggerArea *_STL::vector<AudioTriggerArea, _STL::allocator<AudioTriggerArea > >::erase(AudioTriggerArea *, AudioTriggerArea *);

template AudioTriggerAreaSave *_STL::vector<AudioTriggerAreaSave, _STL::allocator<AudioTriggerAreaSave > >::erase(AudioTriggerAreaSave *, AudioTriggerAreaSave *);

template BfmePod40 * _STL::vector<BfmePod40,_STL::allocator<BfmePod40> >::erase(BfmePod40 *);

template BfmePod40 * _STL::__copy_ptrs<BfmePod40 *,BfmePod40 *>(BfmePod40 *,BfmePod40 *,BfmePod40 *,_STL::__false_type const &);

template BfmePod40 * _STL::vector<BfmePod40,_STL::allocator<BfmePod40> >::erase(BfmePod40 *,BfmePod40 *);

template BfmePod8 * _STL::__copy_ptrs<BfmePod8 const *,BfmePod8 *>(BfmePod8 const *,BfmePod8 const *,BfmePod8 *,_STL::__false_type const &);
