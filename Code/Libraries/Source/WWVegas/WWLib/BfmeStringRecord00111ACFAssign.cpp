// cl: /Ireference/shims/bfme2_ascii /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??4BfmeStringRecord00111ACF@@QAEAAU0@ABU0@@Z @0x00101EF5 60B unlock via rowed set 0x000366F0 plus caller 0x00101FA6 prev 0x00101ECF next 0x00101F5C layout from StringRecordInlineCopyBFME2
#include "ascii_string.h"
struct BfmeStringRecord00111ACF {
    AsciiString first;
    unsigned int word4;
    struct FloatStorage { float values[4]; } middle;
    AsciiString second;
    BfmeStringRecord00111ACF &operator=(const BfmeStringRecord00111ACF &o);
};
BfmeStringRecord00111ACF &BfmeStringRecord00111ACF::operator=(const BfmeStringRecord00111ACF &o)
{
    first = o.first;
    word4 = o.word4;
    for (int i = 0; i < 4; ++i)
        middle.values[i] = o.middle.values[i];
    second = o.second;
    return *this;
}
#include <vector>
template class _STL::vector<BfmeStringRecord00111ACF, _STL::allocator<BfmeStringRecord00111ACF> >;
