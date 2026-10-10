// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// BFME2 record copies with verified StringBase member operations.
// Layouts are read from the complete retail constructors and their STLport
// placement-copy callers. Application names and scalar meanings are unknown.
// String semantics follow BFME1 AsciiString/UnicodeString: the inline derived
// copies call StringBase<char>0x365F0 or StringBase<unsigned short>0x37050.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <memory>
#include "ascii_string.h"
#include "unicode_string.h"

// Retail466EA7 copies an AsciiString and one raw dword. Its bytes are already
// held under the tree-pair identity; use an independently verified alias.
// Application meaning and scalar signedness are not established.
#include <vector>
struct BfmeAsciiScalarValue8 {
    AsciiString text;
    unsigned int value;
    BfmeAsciiScalarValue8();
    BfmeAsciiScalarValue8(const BfmeAsciiScalarValue8 &o)
        : text(o.text), value(o.value) {}
};
template _STL::vector<BfmeAsciiScalarValue8>::vector(const _STL::vector<BfmeAsciiScalarValue8>&);
template class _STL::vector<BfmeAsciiScalarValue8, _STL::allocator<BfmeAsciiScalarValue8> >;
