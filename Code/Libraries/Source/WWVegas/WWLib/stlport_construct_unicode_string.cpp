// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// STLport UnicodeString placement-copy helper at0x54DF6, full45bytes.
// Semantic donor: the exact AsciiString helper in stlport_construct_asciistring.cpp.
// Its direct callee is the established BFME2 StringBase<unsigned short> copy
// constructor at0x37050. The derived string has the same one-pointer layout.

#include "unicode_string.h"
#include <memory>

template void _STL::_Construct<UnicodeString, UnicodeString>(UnicodeString *, const UnicodeString &);
