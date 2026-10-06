// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// STLport placement-copy helper at0x79A41; the direct copy call resolves to
// the independently matched basic_string<char> copy constructor at0x9170.
#include <string>
#include <memory>
template void _STL::_Construct<_STL::basic_string<char>, _STL::basic_string<char> >(_STL::basic_string<char> *,const _STL::basic_string<char> &);
