// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /DNDEBUG /D_STLP_NO_EXCEPTIONS /DWIN32 /D_WINDOWS
// stlport46

#include <rope>
// bfme link decl-only begin
namespace _STL { template <> void allocator<char>::deallocate(char *, unsigned int); }
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, size_t); }
namespace _STL { template <> void * __malloc_alloc<0>::allocate(unsigned int); }
namespace _STL { template <> char *fill_n<unsigned int>(char *, unsigned int, const char &); }
namespace _STL { template <> char *uninitialized_fill_n<char *, unsigned int, char>(char *, unsigned int, const char &); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??$fill_n@I@_STL@@YAPADPADIABD@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> char * fill_n<unsigned int>(char *,unsigned int,char const &); }

// Instantiate the recovered helpers rather than rope's unrelated operations.
namespace _STL {
template bool rope<char, allocator<char> >::empty() const;
template int __lexicographical_compare_3way<char *, char *>(char *, char *, char *, char *);
template ptrdiff_t operator-<char, allocator<char> >(const _Rope_const_iterator<char, allocator<char> > &, const _Rope_const_iterator<char, allocator<char> > &);
template pair<const char *, char *>::pair(const char *const &, char *const &);
template void _Destroy<_Rope_RopeSubstring<char, allocator<char> > >(_Rope_RopeSubstring<char, allocator<char> > *);
}

// Taking the address preserves the recovered out-of-line atomic helper.
typedef long (__cdecl *RopeAtomicSwapFunction)(volatile long *, long);
// ?bfmeRopeAtomicSwapAnchor absent-from-retail
RopeAtomicSwapFunction bfmeRopeAtomicSwapAnchor() { return &_STL::_Atomic_swap; }

// _S_ref is unplaced: the former RVA 0x006C5300 candidate calls GlobalFree,
// not InterlockedIncrement. Its masked DIR32 match did not establish identity.
