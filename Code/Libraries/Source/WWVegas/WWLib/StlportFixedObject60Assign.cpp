// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
// Target copy constructs three sixteen-byte blocks; assignment uses a separate
// member operation. Original type names remain unknown.
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
// Suppress this TU's non-retail copy of ?push_back@?$vector@UBfmeFixedObject60@@V?$allocator@UBfmeFixedObject60@@@_STL@@@_STL@@QAE:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeFixedObject60;
namespace _STL { template <> void vector<BfmeFixedObject60,allocator<BfmeFixedObject60> >::push_back(BfmeFixedObject60 const &); }
// Suppress this TU's non-retail copy of ??$__uninitialized_copy@PAUBfmeFixedObject60@@PAU1@@_STL@@YAPAUBfmeFixedObject60@@PAU1@00A:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> BfmeFixedObject60 * __uninitialized_copy<BfmeFixedObject60 *,BfmeFixedObject60 *>(BfmeFixedObject60 *,BfmeFixedObject60 *,BfmeFixedObject60 *,__false_type const &); }
// Suppress this TU's non-retail copy of ?_M_insert_overflow@?$vector@UBfmeFixedObject60@@V?$allocator@UBfmeFixedObject60@@@_STL@@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void vector<BfmeFixedObject60,allocator<BfmeFixedObject60> >::_M_insert_overflow(BfmeFixedObject60 *,BfmeFixedObject60 const &,__false_type const &,unsigned int,bool); }
// Suppress this TU's non-retail copy of ??$__uninitialized_fill_n@PAUBfmeFixedObject60@@IU1@@_STL@@YAPAUBfmeFixedObject60@@PAU1@IA:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> BfmeFixedObject60 * __uninitialized_fill_n<BfmeFixedObject60 *,unsigned int,BfmeFixedObject60>(BfmeFixedObject60 *,unsigned int,BfmeFixedObject60 const &,__false_type const &); }
// Suppress this TU's non-retail copy of ?allocate@?$allocator@UBfmeFixedObject60@@@_STL@@QBEPAUBfmeFixedObject60@@IPBX@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> BfmeFixedObject60 * allocator<BfmeFixedObject60>::allocate(unsigned int,void const *) const; }

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
struct BfmeFixedBlock16 { unsigned int words[4]; BfmeFixedBlock16(); };
struct BfmeFixedObject60 {
 unsigned int word_00,word_04,word_08;
 BfmeFixedBlock16 blocks_0C[3];
 BfmeFixedObject60();
 BfmeFixedObject60(const BfmeFixedObject60& rhs);
 BfmeFixedObject60& operator=(const BfmeFixedObject60& rhs);
};
typedef char FixedObjectExtent[sizeof(BfmeFixedObject60) == 60 ? 1 : -1];

// Retail keeps these helpers out of line without exception cleanup.
namespace _STL {
template <> __declspec(noinline) inline
BfmeFixedObject60 *__uninitialized_copy<const BfmeFixedObject60 *, BfmeFixedObject60 *>(
    const BfmeFixedObject60 *first, const BfmeFixedObject60 *last,
    BfmeFixedObject60 *result, const __false_type &)
{
    BfmeFixedObject60 *cur = result;
    for (; first != last; ++first, ++cur)
        _Construct(&*cur, *first);
    return cur;
}

template <> template <> __declspec(noinline) inline
BfmeFixedObject60 *vector<BfmeFixedObject60>::_M_allocate_and_copy<const BfmeFixedObject60 *>(
    unsigned int n, const BfmeFixedObject60 *first, const BfmeFixedObject60 *last)
{
    BfmeFixedObject60 *result = this->_M_end_of_storage.allocate(n);
    __uninitialized_copy(first, last, result, _IsPODType());
    return result;
}
}

template _STL::vector<BfmeFixedObject60> & _STL::vector<BfmeFixedObject60>::operator=(const _STL::vector<BfmeFixedObject60> &);
template BfmeFixedObject60 * _STL::vector<BfmeFixedObject60>::erase(BfmeFixedObject60 *, BfmeFixedObject60 *);
template _STL::vector<BfmeFixedObject60>::~vector();
