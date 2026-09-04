// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ios_base::failure, the last of the STLport exception vftables. Its
// destructor is the trivial eleven-byte shape - own vftable store at
// 0x007BCC8C then a tail jump into ~__Named_exception at 0x00023850 - unlike
// the nine <stdexcept> classes, whose destructors the linker took from an /Od
// object. This one and its deleting destructor both came from an optimised
// unit, so one file supplies the pair.

#include <ios>

namespace _STL
{

ios_base::failure::~failure() _STLP_NOTHROW_INHERENTLY
{
}

}
