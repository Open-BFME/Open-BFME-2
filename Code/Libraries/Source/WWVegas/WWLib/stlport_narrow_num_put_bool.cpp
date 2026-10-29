// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport46
//
// STLport num_put<char>::do_put(bool), retail RVA 0x00009450, 385 bytes.
// The boolalpha path follows _num_put.c with ordinary basic_string lifetimes.
// Retail frees all three string buffers inline and retains the locale cleanup.
//
// /D_CRTIMP= keeps free a direct call to the game allocator, and /EHs lets it
// throw, preserving retail's unwind states.
#include <stdlib.h>

#include <stl/_alloc.h>
// Keep retail's inline character-buffer cleanup; the public allocator
// entry point is supplied by its separately verified owner.
namespace _STL {
template <> void __malloc_alloc<0>::deallocate(void *, size_t);
#pragma optimize("gsy", on)
template <> __forceinline void allocator<char>::deallocate(char *p, size_t) { if (p != 0) free(p); }
template <> __forceinline void allocator<unsigned short>::deallocate(unsigned short *p, size_t) { if (p != 0) free(p); }
#pragma optimize("", on)
}

// Keep this TU's inline string storage implementation local.
#define _String_base _String_base_NumPutBool_RV
#include <locale>
// bfme link decl-only begin
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> void * __malloc_alloc<0>::allocate(unsigned int); }
namespace _STL { template <> ostreambuf_iterator<char, char_traits<char> > __copy_integer_and_fill<char, ostreambuf_iterator<char, char_traits<char> > >(char const *, int, ostreambuf_iterator<char, char_traits<char> >, int, int, char, char, char); }
// bfme link decl-only end
// ostreambuf_iterator<char>::operator= and basic_streambuf<char>::sputc are inlined into
// every caller here; retail keeps the out-of-line operator= that calls sputc
// (stlport_ostreambuf_iterator_assign.cpp). Bind it to the kept retail copy instead of
// emitting this unit's own; sputc is spelled through the put area (_M_put is private)
// so it still inlines through the imported operator=.
namespace _STL {
struct _BfmeStreambufPutView { void *_M_vfptr; FILE *_M_get; FILE *_M_put; };
struct _BfmeStreambufOverflow : basic_streambuf<char, char_traits<char> > { using basic_streambuf<char, char_traits<char> >::overflow; };
__declspec(dllimport) __forceinline int _BfmeSputc(basic_streambuf<char, char_traits<char> > *__buf, char __c) {
  int __res;
  FILE *&_M_put = ((_BfmeStreambufPutView *)__buf)->_M_put;
  if (_FILE_O_avail(_M_put) > 0) { _FILE_O_postincr(_M_put) = __c; __res = char_traits<char>::to_int_type(__c); }
  else __res = static_cast<_BfmeStreambufOverflow *>(__buf)->overflow(char_traits<char>::to_int_type(__c));
  return __res;
}
template <> __declspec(dllimport) __forceinline ostreambuf_iterator<char, char_traits<char> > & ostreambuf_iterator<char, char_traits<char> >::operator=(char __c) { _M_ok = _M_ok && !char_traits<char>::eq_int_type(_BfmeSputc(_M_buf, __c), char_traits<char>::eof()); return *this; }
}

// The locale implementation is opaque in _locale.h. Its three vtable slots
// are established by stlport_locale.cpp; visibility here inlines _M_decr.
namespace _STL {
class _Locale_impl {
public:
    virtual ~_Locale_impl();
    virtual void _M_incr();
    virtual void _M_decr();
    locale::facet **_M_facets;
    unsigned int _M_count;
};
// getloc is called out of line here; its COMDAT copy must be retail's
// 0x00007EB0 body, which inlines the locale copy constructor (as in
// stlport_narrow_num_get_bool.cpp and the verified owner stlport_locale.cpp).
inline locale::locale(const locale &that) _STLP_NOTHROW {
    _M_impl = 0;
    _Locale_impl *impl = that._M_impl;
    impl->_M_incr();
    _M_impl = impl;
}
inline locale::~locale() _STLP_NOTHROW { _M_impl->_M_decr(); }


typedef ostreambuf_iterator<char, char_traits<char> > _NarrowOut;

template <> inline _NarrowOut
num_put<char, _NarrowOut>::do_put(_NarrowOut __s, ios_base& __f,
                                  char __fill, bool __val) const {
    if (!(__f.flags() & ios_base::boolalpha))
        return this->do_put(__s, __f, __fill, static_cast<long>(__val));
    locale __loc = __f.getloc();
    const numpunct<char>& __np = *(const numpunct<char>*)__f._M_numpunct_facet();
    basic_string<char> __str(__val ? __np.truename() : __np.falsename());
    ios_base::fmtflags __flags = __f.flags();
    if ((__flags & ios_base::adjustfield) == ios_base::internal)
        __flags = (__flags & ~ios_base::adjustfield) | ios_base::right;
    return __copy_integer_and_fill(__str.c_str(), __str.size(), __s,
                                   __flags, __f.width(0), __fill,
                                   (char)0, (char)0);
}
}

// This boolean formatter is a header inline in the copier units. The anchor
// retains this unit's row copy and is not retail code.
class _StlportNarrowNumPutBoolAnchorAccess
    : public _STL::num_put<char, _STL::_NarrowOut>
{
    friend void _bfmeStlportNarrowNumPutBoolInlineAnchor();
};

#pragma inline_depth(0)
// ?_bfmeStlportNarrowNumPutBoolInlineAnchor@@YAXXZ absent-from-retail
void _bfmeStlportNarrowNumPutBoolInlineAnchor()
{
    static_cast<_StlportNarrowNumPutBoolAnchorAccess *>(0)
        ->_STL::num_put<char, _STL::_NarrowOut>::do_put(
            *static_cast<_STL::_NarrowOut *>(0),
            *static_cast<_STL::ios_base *>(0), 0, false);
}
#pragma inline_depth()

// __copy_integer_and_fill is declared only (stlport_narrow_copy_integer_and_fill.cpp
// owns retail's copy); keep the retail helpers it instantiated here.
template _STL::ostreambuf_iterator<char, _STL::char_traits<char> > _STL::__copy_aux<char const *, _STL::ostreambuf_iterator<char, _STL::char_traits<char> > >(char const *, char const *, _STL::ostreambuf_iterator<char, _STL::char_traits<char> >, _STL::__false_type const &);
template _STL::ostreambuf_iterator<char, _STL::char_traits<char> > _STL::fill_n<_STL::ostreambuf_iterator<char, _STL::char_traits<char> >, int, char>(_STL::ostreambuf_iterator<char, _STL::char_traits<char> >, int, char const &);
template _STL::ostreambuf_iterator<char, _STL::char_traits<char> > _STL::__copy<char const *, _STL::ostreambuf_iterator<char, _STL::char_traits<char> >, int>(char const *, char const *, _STL::ostreambuf_iterator<char, _STL::char_traits<char> >, _STL::random_access_iterator_tag const &, int *);
