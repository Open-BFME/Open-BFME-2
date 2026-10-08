// cl: /Od /Ob1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 vector<void *>, the allocating half. The non-allocating
// bodies live in stlport_vector_voidptr.cpp; these three could not go there
// because the vendored allocator is not the one this game links against.
//
// Retail never reaches __sgi_alloc. _M_allocate_and_copy allocates with
//
//   push 0 / mov eax,[ebp+8] / shl eax,2 / push eax / call 0x000307F0
//
// which is (bytes, hint) __cdecl into the single raw byte allocator that
// symbols.csv already pins - it forwards to the game allocator table at
// 0x00DE0404 with memory class 3. There is no 128-byte small/large split and
// no free-list, which is what the stock header would have produced. _M_clear
// frees through a plain one-argument call to _free at 0x00030830 rather than
// __sgi_alloc::deallocate, so the size argument is computed and discarded.
//
// reference/shims/bfmealloc/stl/_alloc.h is a copy of the vendored header
// with exactly that substitution, and it is opt-in: only a unit that puts the
// shim on its include path sees it.

// Retail does not inline STLport's placement new. push_back at 0x00029140
// reaches _Construct as `push <ptr> / push 4 / call ??2@YAPAXIPAX@Z`, and that
// operator is already in the ledger at 0x00006EE0 as a two-instruction body.
// MSVC's <new> guards its inline definition with __PLACEMENT_NEW_INLINE, so
// defining that macro first suppresses the definition and leaves our
// declaration, which MSVC then has to call.
#define __PLACEMENT_NEW_INLINE
void *__cdecl operator new(unsigned int size, void *place);

#include <vector>

// The native range-erase owner is the 34-byte optimized specialization
// in stlport_vector_voidptr_opt.cpp, not this unit's /Od instantiation.
// Keep its declaration so explicit class instantiation cannot emit a
// competing 84-byte definition. Call sites retain the same symbol and ABI.
template <> void **_STL::vector<void *>::erase(void **first, void **last);

// Native _M_fill_assign calls the distinct 78-byte erase at 0x00027400,
// already owned by vector<unsigned int>. Both views use 12-byte vector
// headers and trivially copied four-byte elements; only this proven range
// ABI is projected here. Preserve that callee rather than substituting the
// optimized void-pointer erase at 0x0031BD55.
template <> unsigned int *_STL::vector<unsigned int>::erase(unsigned int *first, unsigned int *last);

namespace _STL
{
template <> inline vector<void *, allocator<void *> >::iterator
vector<void *, allocator<void *> >::insert(iterator position)
{
    // The retail wrapper retains one more word than the header's discarded
    // inline expansion. This slot models that frame, not an original variable.
    pointer compilerStackSlot;
    value_type value = value_type();
    return insert(position, value);
}
}


namespace _STL {
// VC7.1 /Od retains five discarded words from the visible inline erase
// body in _M_fill_assign's 0x9C frame. The external declaration removes
// that bookkeeping. This empty inline scope preserves those words at
// their original lifetime position; it emits no runtime instructions.
// These are compiler frame slots, not claimed game variables.
static __forceinline void retainEraseCompilerTemporaries() {
    void *first; void *last; void *result; void *begin; void *end;
}
template <> inline void vector<void *>::_M_fill_assign(size_t n, void *const &value) {
    if (n > capacity()) {
        vector<void *> temporary(n, value, get_allocator());
        temporary.swap(*this);
    } else if (n > size()) {
        fill(begin(), end(), value);
        this->_M_finish = _STL::uninitialized_fill_n(this->_M_finish, n-size(), value);
    } else {
        reinterpret_cast<vector<unsigned int> *>(this)->erase(
            reinterpret_cast<unsigned int *>(_STL::fill_n(begin(), n, value)),
            reinterpret_cast<unsigned int *>(end()));
        retainEraseCompilerTemporaries();
    }
}
}

template class _STL::vector<void *, _STL::allocator<void *> >;
