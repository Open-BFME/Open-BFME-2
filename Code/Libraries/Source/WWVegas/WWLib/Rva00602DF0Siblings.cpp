// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ??1istrstream@_STL@@UAE@XZ, retail 0x00602DF0 (89 B).
// First of the three consecutive derived dtors in <strstream> declaration
// order: istrstream 0x00602DF0, ostrstream 0x00602E50 (rowed in
// stlport_ostrstream_dtor.cpp), strstream 0x00602EB0. Derived dtor caller of
// the strstreambuf dtor 0x00602B50.

#include <strstream>

namespace _STL {

istrstream::~istrstream()
{
}

}
