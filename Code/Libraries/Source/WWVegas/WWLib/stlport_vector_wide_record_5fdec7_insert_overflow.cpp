// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?_M_insert_overflow@?$vector@UBfmeContainerRecord005FDEC7@@V?$allocator@UBfmeContainerRecord005FDEC7@@@_STL@@@_STL@@IAEXPAUBfmeContainerRecord005FDEC7@@ABU3@ABU__false_type@2@I_N@Z,
// retail 0x005FE589 183B. STLport 4.5.3 vector growth path for the 12-byte
// wide-string record (word0 word1 UnicodeString at +8) matching the 005FDEC7
// assignment and 005F9217 dtor layout. Same 183B shape as the AnimSet
// 0x001F326F and StringRecordVectorGrowthG7 0x005F9B4E siblings: /G7 emits
// retail imul scaling and edi homing; bfmealloc keeps the two-arg allocate
// call; _Construct declared so copies call the rowed wide-string construct.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

#include "ascii_string.h"
#include "unicode_string.h"

struct BfmeContainerRecord005FDEC7 {
    unsigned int word0;
    unsigned int word1;
    UnicodeString text;
    BfmeContainerRecord005FDEC7(const BfmeContainerRecord005FDEC7 &o);
};

namespace _STL
{
template <> void _Construct<BfmeContainerRecord005FDEC7, BfmeContainerRecord005FDEC7>(BfmeContainerRecord005FDEC7 *, const BfmeContainerRecord005FDEC7 &);
}

template void _STL::vector<BfmeContainerRecord005FDEC7>::reserve(unsigned int);

template void _STL::vector<BfmeContainerRecord005FDEC7>::_M_insert_overflow(
    BfmeContainerRecord005FDEC7 *, const BfmeContainerRecord005FDEC7 &, const _STL::__false_type &, unsigned int, bool);
