// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <ios>

// Retail's generic-widening init is owned by stlport_basic_ios_init.cpp.
// Leave this specialization declared so this unit does not emit a different copy.
namespace _STL {
template <> void basic_ios<char, char_traits<char> >::init(
    basic_streambuf<char, char_traits<char> > *);
}


template class _STL::basic_ios<char, _STL::char_traits<char> >;
