// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Real STLport4.5.3 vector<UnicodeString> reserve family. Semantic donor:
// BFME1 Code/GameEngine/Source/Common/System/XferUnicodeStringVector.cpp.
// BFME2 xfer caller RVA5CD41 calls reserve5A27E, which calls allocate/copy54FAC.
// Its non-POD copy worker54E40 advances four bytes and invokes the independently
// held UnicodeString construction54DF6 -> StringBase<unsigned short> copy37050.
// Clear5A152 calls range destruction56FC0 -> known UnicodeString dtor5B804E.
// The folded allocator68E15 alone is NOT element identity evidence.
// Retail has no container catch path here; the separate placement-copy helper
// keeps its genuine EH frame. Do not globally disable the helper's exceptions.
#include <vector>

#include "unicode_string.h"

// Already recovered from the true wide-string constructor chain in
// stlport_construct_unicode_string.cpp; declaration prevents a different
// local copy-constructor view from replacing that established helper.
namespace _STL {
template <> void _Construct<UnicodeString, UnicodeString>(UnicodeString *, const UnicodeString &);
}

template void _STL::vector<UnicodeString>::reserve(unsigned int);
