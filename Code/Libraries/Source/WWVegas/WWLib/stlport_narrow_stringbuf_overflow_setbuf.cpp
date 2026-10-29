// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

// STLport 4.5.3 narrow basic_stringbuf members that retail compiled with /O1
// (EBP frames, uninlined push_back): overflow (0x1F95C4) and setbuf
// (0x1F9889). Sibling TU stlport_narrow_ostringstream.cpp keeps the base flags.
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

#include <sstream>
// basic_stringbuf<char>'s constructor is the rowed body 0x001F6813
// (stlport_narrow_ostringstream_dtor.cpp); declared so this unit does not emit
// its own constructor chain with a non-retail basic_streambuf<char> constructor.
namespace _STL { template <> basic_stringbuf<char, char_traits<char>, allocator<char> >::basic_stringbuf(int); }
// basic_ostringstream<char>'s constructor is the rowed body 0x001FA85C
// (stlport_narrow_ostringstream_ctor.cpp). Declared here so this unit calls it
// instead of emitting its own constructor chain, whose _STLP_NO_EXCEPTIONS
// basic_streambuf<char> constructor is not retail's.
namespace _STL { template <> basic_ostringstream<char, char_traits<char>, allocator<char> >::basic_ostringstream(int); }

#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> _String_base<char, allocator<char> >::_String_base(allocator<char> const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(); }
namespace _STL { template <> fpos<int>::fpos(long); }
namespace _STL { template <> _String_base<char, allocator<char> >::~_String_base(); }
namespace _STL { template <> basic_stringbuf<char, char_traits<char>, allocator<char> >::~basic_stringbuf(); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::operator=(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> fpos<int> fpos<int>::operator-(long); }
namespace _STL { template <> fpos<int> & fpos<int>::operator-=(long); }
namespace _STL { template <> int basic_stringbuf<char, char_traits<char>, allocator<char> >::_M_xsputnc(char, int); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::append(unsigned int, char); }
namespace _STL { template <> char * __char_traits_base<char, int>::copy(char *, char const *, unsigned int); }
namespace _STL { template <> char * basic_string<char, char_traits<char>, allocator<char> >::erase(char *, char *); }
namespace _STL { template <> char * __char_traits_base<char, int>::move(char *, char const *, unsigned int); }
namespace _STL { template <> void basic_string<char, char_traits<char>, allocator<char> >::push_back(char); }
namespace _STL { template <> void basic_string<char, char_traits<char>, allocator<char> >::reserve(unsigned int); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > basic_stringbuf<char, char_traits<char>, allocator<char> >::str() const; }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?_M_deallocate_block@?$_String_base@DV?$allocator@D@_STL@@@_STL@@QAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void _String_base<char,allocator<char> >::_M_deallocate_block(); }
// Suppress this TU's non-retail copy of ?seekoff@?$basic_stringbuf@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@MAE?AV?$fpos@H@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> fpos<int> basic_stringbuf<char,char_traits<char>,allocator<char> >::seekoff(long,int,int); }
// Suppress this TU's non-retail copy of ?seekpos@?$basic_stringbuf@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@MAE?AV?$fpos@H@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> fpos<int> basic_stringbuf<char,char_traits<char>,allocator<char> >::seekpos(fpos<int>,int); }
// Suppress this TU's non-retail copy of ?xsputn@?$basic_stringbuf@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@MAEHPBDH@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> int basic_stringbuf<char,char_traits<char>,allocator<char> >::xsputn(char const *,int); }
// Suppress this TU's non-retail copy of ??$uninitialized_copy@PADPAD@_STL@@YAPADPAD00@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> char * uninitialized_copy<char *,char *>(char *,char *,char *); }
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char*, size_t);
}
// proxy<char> allocate has no retail body (its retail callers inline it), and
// the STLport 4.6 units no longer emit this 4.5.3 copy: this unit provides it
// for the 4.5.3 consumers that declare it without a body.
template class _STL::basic_stringbuf<char, _STL::char_traits<char>, _STL::allocator<char> >;
