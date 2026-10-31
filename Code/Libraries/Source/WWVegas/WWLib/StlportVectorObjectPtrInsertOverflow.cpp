// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 vector<Object*>::_M_insert_overflow (__true_type) at
// 0x001F2155/147, the growth path of the rowed vector<Object*>::push_back
// 0x001F211B (StlportVectorPushBackSiblings.cpp).
// Target evidence: retail keeps an EBP frame with no EH state (push ebp ...
// leave; ret 0x14) and size-optimized cdecl cleanup (pop ecx; pop ecx), which
// /O1 /Oy- reproduces; the zero-length allocation guard calls the rowed byte
// allocator 0x000307F0, both copies the rowed __copy_trivial 0x000179B0, and
// the old storage is released by an out-of-line call to the 14-byte
// free-first-pointer body at 0x0007FAB3 (this instantiation's _M_clear, an
// ICF fold of the rowed vector teardowns there).
// Donor: STLport 4.5.3 _vector.c __true_type _M_insert_overflow (copy, fill_n,
// copy, _M_clear, _M_set); the zero-length guard is target-observed.
#include <stl/_algobase.h>
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row).
// This unit-local overload keeps the inlined code and offers the link no
// second copy.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

class Object;

namespace _STL {

// STLport's fill_n is not expanded at this unit's /O1; retail inlines the
// fill loop with fill_n's own shape (count in ecx, cursor in eax, the value
// re-read through its reference each pass).
static inline Object **FillObjectPointers(Object **first, unsigned int n, Object * const &value)
{
    for (; n > 0; --n, ++first)
        *first = value;
    return first;
}

// Retail calls _M_clear out of line (0x0007FAB3) rather than expanding it.
template <> __declspec(noinline) void vector<Object *>::_M_clear();

template <> void vector<Object *>::_M_insert_overflow(Object **__position, Object * const &__x,
    const __true_type &, unsigned int __fill_len, bool __atend)
{
    const unsigned int __old_size = size();
    const unsigned int __len = __old_size + (max)(__old_size, __fill_len);
    pointer __new_start = __len ? (pointer)allocator<char>::allocate(__len * sizeof(Object *), 0) : 0;
    pointer __new_finish = (pointer)__copy_trivial(this->_M_start, __position, __new_start);
    __new_finish = FillObjectPointers(__new_finish, __fill_len, __x);
    if (!__atend)
        __new_finish = (pointer)__copy_trivial(__position, this->_M_finish, __new_finish);
    _M_clear();
    _M_set(__new_start, __new_finish, __new_start + __len);
}

template <> void vector<Object *>::_M_clear()
{
    _Destroy(this->_M_start, this->_M_finish);
    this->_M_end_of_storage.deallocate(this->_M_start, this->_M_end_of_storage._M_data - this->_M_start);
}

}

template void _STL::vector<Object *>::_M_insert_overflow(Object **, Object * const &,
    const _STL::__true_type &, unsigned int, bool);
