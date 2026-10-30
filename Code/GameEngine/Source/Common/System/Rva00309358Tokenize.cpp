// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
// ?Rva00309358Tokenize@@YAXABV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@AAV?$vector@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@V?$allocator@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@@2@@2@0@Z
// Retail 0x00309358 158 bytes cdecl with an EH frame for the substr temporary.
// The classic string tokenizer: clear the output then find_first_not_of
// (rowed 0x0002A3A0 through the (data size) overload) and find_first_of
// (rowed 0x00028C10) the delimiters; while either position is live push the
// substr (rowed 0x0002AD50) temporary straight into push_back (rowed
// 0x0007A773) then advance with find_first_not_of (rowed 0x0002AC90) and
// find_first_of again. MSVC tail-merges the two find_first_of calls into the
// loop head which is why retail reloads the end position from its slot.
// Original helper name unknown; semantics established by native STL range
// calls and independently by StandingWaterArea::LoadPCAFile (WB BDE250).
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
// codegen otherwise instantiates the min<unsigned> COMDAT (one byte shape
// per TU flags); a file-static overload takes those calls instead so this
// TU emits no external copy.
namespace _STL {
static inline const unsigned int &min(const unsigned int &a, const unsigned int &b)
{
    return b < a ? b : a;
}
}
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <string>
#include <vector>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> void vector<basic_string<char,char_traits<char>,allocator<char> >,allocator<basic_string<char,char_traits<char>,allocator<char> > > >::push_back(basic_string<char,char_traits<char>,allocator<char> > const &); }
// bfme link decl-only begin
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > * __uninitialized_copy<basic_string<char, char_traits<char>, allocator<char> > *, basic_string<char, char_traits<char>, allocator<char> > *>(basic_string<char, char_traits<char>, allocator<char> > *, basic_string<char, char_traits<char>, allocator<char> > *, basic_string<char, char_traits<char>, allocator<char> > *, __false_type const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > * __uninitialized_fill_n<basic_string<char, char_traits<char>, allocator<char> > *, unsigned int, basic_string<char, char_traits<char>, allocator<char> > >(basic_string<char, char_traits<char>, allocator<char> > *, unsigned int, basic_string<char, char_traits<char>, allocator<char> > const &, __false_type const &); }
namespace _STL { template <> _String_base<char, allocator<char> >::_String_base(allocator<char> const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::operator=(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> void vector<basic_string<char, char_traits<char>, allocator<char> >, allocator<basic_string<char, char_traits<char>, allocator<char> > > >::_M_insert_overflow(basic_string<char, char_traits<char>, allocator<char> > *, basic_string<char, char_traits<char>, allocator<char> > const &, __false_type const &, unsigned int, bool); }
namespace _STL { template <> char * basic_string<char, char_traits<char>, allocator<char> >::erase(char *, char *); }
namespace _STL { template <> char * __char_traits_base<char, int>::move(char *, char const *, unsigned int); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > basic_string<char, char_traits<char>, allocator<char> >::substr(unsigned int, unsigned int) const; }
// bfme link decl-only end
// Keep _STLP_alloc_proxy<char*>::deallocate inline-only: this TU never calls it
// out of line, and its COMDAT copy (unit flags) differs from retail's 0x006892B0 body.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char *__p, size_t __n)
{ allocator<char>::deallocate(__p, __n); }
}

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
void Rva00309358Tokenize(const std::string &text,std::vector<std::string> &words,const std::string &delimiters)
{
 words.erase(words.begin(),words.end());
 unsigned begin=text.find_first_not_of(delimiters,0);
 unsigned end=text.find_first_of(delimiters,begin);
 while(end!=std::string::npos || begin!=std::string::npos)
 {
  words.push_back(text.substr(begin,end-begin));
  begin=text.find_first_not_of(delimiters,end);
  end=text.find_first_of(delimiters,begin);
 }
}
