// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// STLport 4.5.3 basic_ios<wchar_t>::imbue (stl/_ios.c), retail 0x00016200,
// 238 bytes: vendor body with its inlined grouping assignment expressed by
// a TU-local helper. The wide twin of stlport_narrow_ios_imbue.cpp.
//
// _STLP_USE_MALLOC frees the cached grouping string's old buffer with plain
// free rather than the node allocator's size-checked operator delete, and
// _CRTIMP= makes that a direct call instead of one through the CRT import.
// The grouping itself comes from numpunct<wchar_t>::grouping, which the linker
// folded with the identical narrow getter at 0x00015E50.

// The cached grouping string is assigned through vendor's private
// _M_assign_dispatch<char*>, whose matched body is at 0x000120F0.
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <stl/_alloc.h>
// Keep retail's inline character-buffer cleanup; the public allocator
// entry point is supplied by its separately verified owner.
namespace _STL {
template <> void __malloc_alloc<0>::deallocate(void *, size_t);
template <> void *__malloc_alloc<0>::allocate(size_t);
#pragma optimize("gsy", on)
template <> __forceinline void allocator<char>::deallocate(char *p, size_t) const { if (p != 0) free(p); }
template <> __forceinline void allocator<unsigned short>::deallocate(unsigned short *p, size_t) const { if (p != 0) free(p); }
#pragma optimize("", on)
}

#include <string>
#include <ios>

#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> char * basic_string<char, char_traits<char>, allocator<char> >::erase(char *, char *); }
namespace _STL { template <> char * __char_traits_base<char, int>::move(char *, char const *, unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??$uninitialized_copy@PADPAD@_STL@@YAPADPAD00@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> char * uninitialized_copy<char *,char *>(char *,char *,char *); }
// Suppress this TU's non-retail copy of ??$__copy_ptrs@PADPAD@_STL@@YAPADPAD00ABU__true_type@0@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> char *__copy_ptrs<char *, char *>(char *, char *, char *, const __true_type &); }
// Suppress this TU's non-retail copy of ??$__copy_aux@PADPAD@_STL@@YAPADPAD00ABU__true_type@0@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> char *__copy_aux<char *, char *>(char *, char *, char *, const __true_type &); }
// Suppress this TU's non-retail copy of ??$__uninitialized_copy@PADPAD@_STL@@YAPADPAD00ABU__true_type@0@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> char *__uninitialized_copy<char *, char *>(char *, char *, char *, const __true_type &); }
// Keep the remaining 4.5.3 consumers supplied while the narrow imbue unit
// moves to 4.6: let the vendor emit its proxy<char> allocate helper here.
namespace _STL {
// TU-local forceinline helper standing in for the inlined copy-assignment body:
// same self-check plus pointer-range dispatch, temp bound by const reference so
// the call keeps the vendor statement's full-expression lifetime. The range is
// read through the public const begin()/end() accessors; const_cast restores
// the char* iterator type the matched dispatch body takes, so the call still
// binds _M_assign_dispatch<char*> at 0x000120F0.
static __forceinline void bfme_cached_grouping_assign(
        basic_string<char, char_traits<char>, allocator<char> > &__dst,
        const basic_string<char, char_traits<char>, allocator<char> > &__src)
{
  if (&__src != &__dst)
    __dst.assign(const_cast<char *>(__src.begin()), const_cast<char *>(__src.end()));
}
}

// Suppress this TU's non-retail copy of ??4?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAEAAV01@ABV01@@Z
// (narrow basic_string<char>::operator=): the kept copy serves the link; its row
// owner is stlport_narrow_string_assign_copy.cpp at 0x000120C0. Plain
// declaration-only form (no __imp_).
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::operator=(const basic_string<char, char_traits<char>, allocator<char> > &); }
template <>
inline _STL::locale _STL::basic_ios<wchar_t, _STL::char_traits<wchar_t> >::imbue(const _STL::locale &__loc)
{
  _STL::locale __tmp = ios_base::imbue(__loc);

  if (_M_streambuf)
    _M_streambuf->pubimbue(__loc);

  // no throwing here
  this->_M_cached_ctype = __loc._M_get_facet(ctype<char_type>::id) ;
  this->_M_cached_numpunct = __loc._M_get_facet(numpunct<char_type>::id) ;
  bfme_cached_grouping_assign(this->_M_cached_grouping, ((numpunct<char_type>*)_M_cached_numpunct)->grouping()) ;
  return __tmp;
}

// Emit the inline specialization as a foldable template copy, like the
// vendor instantiation, alongside other stream units using the same member.
template _STL::locale _STL::basic_ios<wchar_t, _STL::char_traits<wchar_t> >::imbue(const _STL::locale &);
