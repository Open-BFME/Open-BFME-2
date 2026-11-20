// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// vector<BfmeE8>::_M_fill_insert, retail 0x000B02B6, 223 bytes, plus the two
// instantiations MSVC must see to emit that shape.
//
// The body was first placed under the BfmePod8 spelling by a masked whole-.text
// search, which proves size and element stride but not identity. Retail's own
// call sites prove the element: this body calls __uninitialized_copy
// 0x004C3121 and _M_insert_overflow 0x00057C80, both the E8 instantiation's
// rows, plus fill 0x000AD7E4, __copy_backward_ptrs 0x0030B378 and
// uninitialized_fill_n 0x005FF4DD. The BfmePod8 copy of __uninitialized_copy
// is a different body at 0x004C3ACC (its _Construct is 0x004C3A9F, and only
// the Rva004C3F09Element overflow calls it), which retail never calls here.
//
// Shape: this unit includes the vendor stl/_algobase.h, not
// reference/shims/bfmealloc, whose __forceinline __copy_backward_ptrs is
// inlined into a 231-byte body; vendor's plain inline leaves retail's
// out-of-line call to 0x0030B378. MSVC 7.1 packs the empty __false_type tag
// onto the dead incoming-argument slot only when it sees the callee bodies, so
// __uninitialized_copy (retail's 38-byte 0x004C3121 loop) and
// _M_insert_overflow (retail's 184-byte 0x00057C80 path) are instantiated here
// instead of being left to declaration-only calls, which give 244/228 and 178
// bytes.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

struct Rva0060C9D9Element;
namespace _STL {
// 0x0060C9D9, rowed in StlSweepW6Rva0060C9D9.cpp: the out-of-line _Construct
// that retail's 0x004C3121 copy calls.
template <> void _Construct<Rva0060C9D9Element, Rva0060C9D9Element>(Rva0060C9D9Element *, const Rva0060C9D9Element &);
// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs; explicit dllimport+forceinline specializations take those calls
// inline so this TU emits no external copies.
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}
struct BfmeE8 { int a[2]; };
namespace _STL {
// allocator<BfmeE8>::allocate is kept from the bfmealloc pod units (retail's
// 0x00523D6C fold); declare it so this malloc-configured unit emits no copy.
template <> BfmeE8 *allocator<BfmeE8>::allocate(size_t, const void *) const;
// Retail 0x004C3121: the implicit instantiation, same shape as in
// stlport_vector_e8_o1.cpp.
template BfmeE8 *__uninitialized_copy<BfmeE8 *, BfmeE8 *>(BfmeE8 *, BfmeE8 *, BfmeE8 *, const __false_type &);
// Retail 0x00057C80: the no-EH growth path, with _M_clear inlined.
template <> inline void vector<BfmeE8>::_M_insert_overflow(
    pointer position, const BfmeE8 &value, const __false_type &,
    size_type fillLength, bool atEnd)
{
    const size_type oldSize = size();
    const size_type length = oldSize + (max)(oldSize, fillLength);
    pointer start = this->_M_end_of_storage.allocate(length);
    pointer finish = start;
    finish = __uninitialized_copy(this->_M_start, position, start, __false_type());
    if (fillLength == 1) {
        _Construct(finish, value);
        ++finish;
    } else
        finish = __uninitialized_fill_n(finish, fillLength, value, __false_type());
    if (!atEnd)
        finish = __uninitialized_copy(position, this->_M_finish, finish, __false_type());
    _M_clear();
    _M_set(start, finish, start + length);
}
}
// Instantiate the matched member without unrelated container operations.
template void _STL::vector<BfmeE8, _STL::allocator<BfmeE8> >::_M_fill_insert(BfmeE8 *, unsigned int, BfmeE8 const &);
