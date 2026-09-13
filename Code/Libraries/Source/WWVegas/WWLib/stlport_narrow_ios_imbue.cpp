// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// STLport 4.5.3 basic_ios<char>::imbue (stl/_ios.c), retail 0x00016110, 238
// bytes: the vendor body verbatim, instantiated on its own.
//
// Two build settings decide the bytes. _STLP_USE_MALLOC frees the cached
// grouping string's old buffer with plain free rather than the node
// allocator's size-checked operator delete, and _CRTIMP= makes that a direct
// call instead of one through the CRT import.

// The cached grouping string is assigned through _M_assign_dispatch<char*>,
// whose matched body at 0x000120F0 carries the public member signature in this
// reconstruction. Limit this access adaptation to the string header; layout
// and source semantics are unchanged.
#define private public
#include <string>
#undef private
#include <ios>

template _STL::locale _STL::basic_ios<char, _STL::char_traits<char> >::imbue(const _STL::locale &);
