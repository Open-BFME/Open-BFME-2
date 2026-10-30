// cl: /O1 /Ob2 /D_CRTIMP= /arch:SSE /G7 /Oy- /MD /EHs /DNDEBUG /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <string>
#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> _String_base<char, allocator<char> >::_String_base(allocator<char> const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(_String_reserve_t, unsigned int, allocator<char> const &); }
namespace _STL { template <> void basic_string<char, char_traits<char>, allocator<char> >::_M_construct_null(char *); }
namespace _STL { template <> void basic_string<char, char_traits<char>, allocator<char> >::_M_construct_null_aux(char *, __true_type const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::append(basic_string<char, char_traits<char>, allocator<char> > const &); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??$uninitialized_copy@PADPAD@_STL@@YAPADPAD00@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> char * uninitialized_copy<char *,char *>(char *,char *,char *); }
// Suppress this TU's non-retail copy of ??$__uninitialized_copy@PADPAD@_STL@@YAPADPAD00ABU__true_type@0@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> char *__uninitialized_copy<char *, char *>(char *, char *, char *, const __true_type &); }
// Keep _STLP_alloc_proxy<char*>::deallocate inline-only: this TU never calls it
// out of line, and its COMDAT copy (unit flags) differs from retail's 0x006892B0 body.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char *__p, size_t __n)
{ allocator<char>::deallocate(__p, __n); }
}
// Suppress this TU's non-retail proxy<char> allocate copy (family2-LK3 row 30):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> __declspec(dllimport) __forceinline
char *_STLP_alloc_proxy<char*, char, allocator<char> >::allocate(size_t __n)
{ return __n != 0 ? allocator<char>::allocate(__n * sizeof(char), 0) : 0; }
}

// Retail boundary 001F9524 160B; caller 001FB46F appends the template name.
// STLport string concatenation lead; copied/reserved narrow storage and forward-iterator append
// are target facts. The shared empty allocator getter is the rowed wide provider at 001627F0.
typedef _STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char> > NarrowString;
typedef _STL::basic_string<unsigned short,_STL::char_traits<unsigned short>,_STL::allocator<unsigned short> > WideString;
NarrowString Rva001F9524Concat(const NarrowString &first,const char *second) {
 unsigned n=strlen(second);
 NarrowString tmp(_STL::_String_reserve_t(),first.size()+n,*(const _STL::allocator<char>*)&((const WideString&)first).get_allocator());
 tmp.append(first); tmp.append(second,second+n); return tmp;
}
