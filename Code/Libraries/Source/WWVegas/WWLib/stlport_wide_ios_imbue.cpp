// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// STLport 4.5.3 basic_ios<wchar_t>::imbue (stl/_ios.c), retail 0x00016200,
// 238 bytes: the vendor body verbatim, the wide twin of
// stlport_narrow_ios_imbue.cpp built the same way.
//
// _STLP_USE_MALLOC frees the cached grouping string's old buffer with plain
// free rather than the node allocator's size-checked operator delete, and
// _CRTIMP= makes that a direct call instead of one through the CRT import.
// The grouping itself comes from numpunct<wchar_t>::grouping, which the linker
// folded with the identical narrow getter at 0x00015E50.

// The cached grouping string is assigned through _M_assign_dispatch<char*>,
// whose matched body at 0x000120F0 carries the public member signature in this
// reconstruction. Limit this access adaptation to the string header; layout
// and source semantics are unchanged.
#define private public
#include <string>
#undef private
#include <ios>

template _STL::locale _STL::basic_ios<wchar_t, _STL::char_traits<wchar_t> >::imbue(const _STL::locale &);
