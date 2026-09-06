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

template class _STL::vector<void *, _STL::allocator<void *> >;
