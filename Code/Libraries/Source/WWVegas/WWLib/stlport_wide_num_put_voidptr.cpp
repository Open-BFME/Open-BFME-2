// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
//
// The wide twin of stlport_narrow_num_put_voidptr.cpp: num_put<wchar_t>'s
// do_put(const void*), vtable slot 1 of 0x007BBAA8. Same shipped-source
// deviation - the dead `locale __loc = __f.getloc();` is not in the source the
// game was built against - and the same 107-byte straight-line result, because
// widen() is a virtual call either way and the element width never reaches
// this body.

#include <locale>

_STLP_BEGIN_NAMESPACE

typedef ostreambuf_iterator<wchar_t, char_traits<wchar_t> > _WideOut;

_STLP_TEMPLATE_NULL
_WideOut
num_put<wchar_t, _WideOut>::do_put(_WideOut __s, ios_base& __f, wchar_t,
                                   const void* __val) const
{
  const ctype<wchar_t>& __c_type = *(const ctype<wchar_t>*)__f._M_ctype_facet();
  ios_base::fmtflags __save_flags = __f.flags();

  __f.setf(ios_base::hex, ios_base::basefield);
  __f.setf(ios_base::showbase);
  __f.setf(ios_base::internal, ios_base::adjustfield);
  __f.width((sizeof(void*) * 2) + 2);
  _WideOut result = this->do_put(__s, __f, __c_type.widen('0'),
                                 __REINTERPRET_CAST(unsigned _STLP_LONG_LONG, __val));
  __f.flags(__save_flags);
  return result;
}

_STLP_END_NAMESPACE
