// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Target-specific placement construction wrapper for the neutral record view.
#include "Object156.h"
#include <new>

namespace _STL {
template<> void _Construct<BfmeOpaqueRecord156, BfmeOpaqueRecord156>(
	BfmeOpaqueRecord156 *dest, const BfmeOpaqueRecord156 &source) throw()
{
	new (dest) BfmeOpaqueRecord156(source);
}
}
