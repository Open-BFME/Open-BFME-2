// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46

#include <streambuf>

namespace _STL
{
// Suppress the differing xsgetn COMDAT; retail's copy is owned by
// stlport_wide_stringbuf.cpp (0x00013870). Whole-class instantiation would
// otherwise emit our own wrong copy (virtual uflow call vs retail sbumpc call).
template <>
int basic_streambuf<wchar_t, char_traits<wchar_t> >::xsgetn(wchar_t*, int);
}

template class _STL::basic_streambuf<wchar_t, _STL::char_traits<wchar_t> >;
