// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// STLport donor: reference/open-bfme-1/vendor/stlport/stl/_vector.h.
// Target assignment 0x5FDEC7 copies words +0/+4 and sets the wide string at +8.
// The destroy loop confirms a 12-byte stride; application identity is unknown.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include "unicode_string.h"
struct BfmeContainerRecord005FDEC7 {
    unsigned int word0;
    unsigned int word4;
    UnicodeString text08;
    BfmeContainerRecord005FDEC7();
    __declspec(nothrow) BfmeContainerRecord005FDEC7 &operator=(const BfmeContainerRecord005FDEC7 &other);
};
__declspec(nothrow) BfmeContainerRecord005FDEC7 &BfmeContainerRecord005FDEC7::operator=(const BfmeContainerRecord005FDEC7 &other) {
    word0 = other.word0;
    word4 = other.word4;
    text08 = other.text08;
    return *this;
}
#include <vector>
template class _STL::vector<BfmeContainerRecord005FDEC7, _STL::allocator<BfmeContainerRecord005FDEC7> >;
