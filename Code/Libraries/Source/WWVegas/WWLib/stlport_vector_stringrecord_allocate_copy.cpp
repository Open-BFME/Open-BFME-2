// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// BFME2's 36-byte StringRecord vector allocation/copy helper at RVA 0x64405.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

class AsciiString { public: AsciiString(const AsciiString &); __forceinline ~AsciiString(); protected: void releaseBuffer(); private: void *m_data; };
struct BfmeStringRecord00063BE4 {
    unsigned int word0, word1, word2, word3, word4, word5, word6;
    AsciiString text;
    unsigned char tail0, tail1;
    BfmeStringRecord00063BE4();
    BfmeStringRecord00063BE4(const BfmeStringRecord00063BE4 &o)
      : word0(o.word0), word1(o.word1), word2(o.word2), word3(o.word3), word4(o.word4), word5(o.word5), word6(o.word6), text(o.text), tail0(o.tail0), tail1(o.tail1) {}
};
#include <memory>
template void _STL::_Construct<BfmeStringRecord00063BE4,BfmeStringRecord00063BE4>(BfmeStringRecord00063BE4*,const BfmeStringRecord00063BE4&);
#include <vector>
template class _STL::vector<BfmeStringRecord00063BE4, _STL::allocator<BfmeStringRecord00063BE4> >;
