// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?reserve@?$vector@UBfmeVectorRecord00319C84@@...@QAEXI@Z, retail 0x00319C84, 105 bytes.
// Evidence: the body is byte-identical to vector<BfmeVectorRecord0002154F3>::reserve
// except its _M_clear call, which reads 0x00565A60 rather than that vector's
// rowed _M_clear at 0x0021580E. Its _M_allocate_and_copy call reads 0x00319304,
// also apart from that vector's other bodies near 0x002155xx. So this is a second
// instantiation over an element type with the same 16-byte layout; the type name
// is generated and the layout is copied from BfmeVectorRecord0002154F3.
// Uses the shared ascii_string.h so the emitted ??_GAsciiString copy calls
// releaseBuffer like the kept WOLBuddyOverlay copy.
#include "ascii_string.h"
#include <vector>
struct BfmeVectorRecord00319C84 {
    AsciiString text;
    _STL::vector<AsciiString> names;
    BfmeVectorRecord00319C84();
    BfmeVectorRecord00319C84(const BfmeVectorRecord00319C84 &);
};
namespace _STL {
template <> void _Construct<BfmeVectorRecord00319C84, BfmeVectorRecord00319C84>(BfmeVectorRecord00319C84 *, const BfmeVectorRecord00319C84 &);
}
template void _STL::vector<BfmeVectorRecord00319C84, _STL::allocator<BfmeVectorRecord00319C84> >::reserve(size_t);
