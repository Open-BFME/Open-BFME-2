// cl: /Od /Ob1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /DNDEBUG /D_STLP_NO_EXCEPTIONS /DWIN32 /D_WINDOWS
// stlport46
//
// STLport 4.5.3 vector<void *> copy constructor at 0x000272A0 (200 bytes).
//
// The body is the stock vendored header's
//   vector(const vector& __x) : _Vector_base(__x.size(), __x.get_allocator()) {
//     _M_finish = __uninitialized_copy(__x._M_start, __x._M_finish, _M_start,
//                                      _IsPODType());
//   }
// with the shim's POD dispatch collapsing to the out-of-line __copy_trivial
// (0x000179B0), the get_allocator (0x00023B50) and _Vector_base(size, alloc)
// (0x00025140) calls, and the allocator replaced by reference/shims/bfmealloc.
//
// The only deviation from the shipped shim is a TU-scoped `__declspec(nothrow)`
// redeclaration of __copy_trivial. Without it cl treats the copy helper as
// possibly throwing, keeps a second C++ EH cleanup region alive (an 0x272F5
// byte-width state store), and emits 199 bytes. Retail's 200-byte body has no
// cleanup region after _Vector_base, so the shipped declaration carries the
// nothrow attribute; the redeclaration is local to this unit and changes no
// shared header.

namespace _STL { __declspec(nothrow) void* __copy_trivial(const void*, const void*, void*); }

#include <vector>

// The native range-erase owner is the 34-byte optimized specialization
// in stlport_vector_voidptr_opt.cpp, not this unit's /Od instantiation.
// Keep its declaration so explicit class instantiation cannot emit a
// competing 84-byte definition. Call sites retain the same symbol and ABI.
template <> void **_STL::vector<void *>::erase(void **first, void **last);
// The allocating unit owns the verified fill-assign specialization.
template <> void _STL::vector<void *>::_M_fill_assign(size_t n, void *const &value);
// The allocating unit now owns the verified 525-byte fill-insert body.
// Keep this unit's primary-template copy out of COMDAT selection.
template <> void _STL::vector<void *>::_M_fill_insert(void **position, size_t n, void *const &value);
// Likewise, the allocating unit owns native insertion at 0x000291D0.
template <> void **_STL::vector<void *>::insert(void **position, void *const &value);

// Suppress this unit's non-retail clear copy (row 57 family2-LK3) so the link
// keeps the retail copy another unit provides.
namespace _STL {
template <> void _STL::vector<void *>::clear();
}

// Instantiate only the copy constructor this unit owns: a whole-class
// instantiation also emitted this unit's /Od copies of every other member,
// which compete with the owners' bodies (operator= among them).
template _STL::vector<void *, _STL::allocator<void *> >::vector(const _STL::vector<void *, _STL::allocator<void *> > &);
