// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ??1strstream@_STL@@UAE@XZ, retail 0x00602EB0 (129 B).
// Last of the three consecutive derived strstream dtors in <strstream>
// declaration order: istrstream 0x00602DF0 (Rva00602DF0Siblings.cpp),
// ostrstream 0x00602E50 (stlport_ostrstream_dtor.cpp), strstream 0x00602EB0.
// It is the widest of the three because strstream derives from iostream and so
// restores iostream's two base vftables plus the strstreambuf one. Derived dtor
// caller of the strstreambuf dtor 0x00602B50. Empty user body: the stores and
// the base-dtor call are all compiler-generated, exactly as in the two rowed
// siblings.

#include <strstream>

namespace _STL {

strstream::~strstream()
{
}

}
