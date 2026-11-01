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
// The const-copy helpers of the two operator= bodies call retail's rowed
// element copy bodies: 0x005385F3 calls 0x00469C61 and 0x004C3121 calls
// 0x0060C9D9. These are call-target bindings, not element identities.
struct BfmePod16;
struct BfmePod8;
struct BfmeFloat4Record00469C61;
struct Rva0060C9D9Element;
namespace _STL {
template <> void _Construct<BfmeFloat4Record00469C61, BfmeFloat4Record00469C61>(BfmeFloat4Record00469C61 *, const BfmeFloat4Record00469C61 &);
template <> void _Construct<Rva0060C9D9Element, Rva0060C9D9Element>(Rva0060C9D9Element *, const Rva0060C9D9Element &);
// 0x00469C61
template <> __declspec(dllimport) __forceinline void _Construct<BfmePod16, BfmePod16>(BfmePod16 *p, const BfmePod16 &v)
{ _Construct((BfmeFloat4Record00469C61 *)p, (const BfmeFloat4Record00469C61 &)v); }
// 0x0060C9D9
template <> __declspec(dllimport) __forceinline void _Construct<BfmePod8, BfmePod8>(BfmePod8 *p, const BfmePod8 &v)
{ _Construct((Rva0060C9D9Element *)p, (const Rva0060C9D9Element &)v); }
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
struct BfmePod68;
namespace _STL { template <> void vector<BfmePod68,allocator<BfmePod68> >::_M_insert_overflow(BfmePod68 *,BfmePod68 const &,__false_type const &,unsigned int,bool); }
// Suppress this TU's non-retail copy of ?allocate@?$allocator@UBfmePod16@@@_STL@@QBEPAUBfmePod16@@IPBX@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod16;
namespace _STL { template <> BfmePod16 * allocator<BfmePod16>::allocate(unsigned int,void const *) const; }
// Suppress this TU's non-retail copy of ?resize@?$vector@UBfmePod44@@V?$allocator@UBfmePod44@@@_STL@@@_STL@@QAEXI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod44;
namespace _STL { template <> void vector<BfmePod44, allocator<BfmePod44> >::resize(size_t); }
// Suppress this TU's non-retail copy of ?allocate@?$allocator@UBfmePod8@@@_STL@@QBEPAUBfmePod8@@IPBX@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod8;
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
// Retail's const-copy helpers of the two operator= bodies (0x001D9AD9 and
// 0x004C3121 for 8 bytes, 0x0007C25C and 0x005385F3 for 16) have no unwind
// path although this unit enables exceptions: STLport's no-EH bodies
// (as in stlport_vector_e8_o1.cpp).
namespace _STL {
template <> inline BfmePod8 *__uninitialized_copy<const BfmePod8 *, BfmePod8 *>(const BfmePod8 *first, const BfmePod8 *last, BfmePod8 *result, const __false_type &)
{ BfmePod8 *cur = result; for (; first != last; ++first, ++cur) _Construct(cur, *first); return cur; }
template <> template <> inline BfmePod8 *vector<BfmePod8>::_M_allocate_and_copy<const BfmePod8 *>(size_t n, const BfmePod8 *first, const BfmePod8 *last)
{ pointer result = this->_M_end_of_storage.allocate(n); __uninitialized_copy(first, last, result, __false_type()); return result; }
}
namespace _STL {
template <> inline BfmePod16 *__uninitialized_copy<const BfmePod16 *, BfmePod16 *>(const BfmePod16 *first, const BfmePod16 *last, BfmePod16 *result, const __false_type &)
{ BfmePod16 *cur = result; for (; first != last; ++first, ++cur) _Construct(cur, *first); return cur; }
template <> template <> inline BfmePod16 *vector<BfmePod16>::_M_allocate_and_copy<const BfmePod16 *>(size_t n, const BfmePod16 *first, const BfmePod16 *last)
{ pointer result = this->_M_end_of_storage.allocate(n); __uninitialized_copy(first, last, result, __false_type()); return result; }
}
struct BfmePod40 { int a[10]; };
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
// Instantiate the matched members without unrelated container operations.

template _STL::vector<BfmePod8,_STL::allocator<BfmePod8> > & _STL::vector<BfmePod8,_STL::allocator<BfmePod8> >::operator=(_STL::vector<BfmePod8,_STL::allocator<BfmePod8> > const &);


template BfmePod8 * _STL::vector<BfmePod8,_STL::allocator<BfmePod8> >::erase(BfmePod8 *);

template BfmePod8 * _STL::vector<BfmePod8,_STL::allocator<BfmePod8> >::erase(BfmePod8 *,BfmePod8 *);



template _STL::vector<BfmePod16,_STL::allocator<BfmePod16> > & _STL::vector<BfmePod16,_STL::allocator<BfmePod16> >::operator=(_STL::vector<BfmePod16,_STL::allocator<BfmePod16> > const &);

