// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ??1ostrstream@_STL@@UAE@XZ, retail 0x00602E50 (89 B).
// Derived dtor caller of strstreambuf dtor 0x00602B50 (see
// stlport_strstreambuf_dtor.cpp: callers 0x00602DF0 0x00602E50 0x00602EB0).
// Middle of the three consecutive derived dtors; ostrstream is the middle
// declaration in <strstream> (istrstream, ostrstream, strstream).

#include <strstream>

namespace _STL {

ostrstream::~ostrstream()
{
}

}
