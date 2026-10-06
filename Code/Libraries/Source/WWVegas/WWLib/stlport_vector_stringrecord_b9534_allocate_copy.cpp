// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// BFME2's 24-byte StringRecord vector allocation/copy helper at RVA 0xBBCEF.
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
struct BfmeStringRecord000B9534 {
    AsciiString text;
    unsigned char flag;
    unsigned int word0, word1, word2, word3;
    BfmeStringRecord000B9534();
    BfmeStringRecord000B9534(const BfmeStringRecord000B9534 &o)
      : text(o.text), flag(o.flag), word0(o.word0), word1(o.word1), word2(o.word2), word3(o.word3) {}
};
#include <memory>
template void _STL::_Construct<BfmeStringRecord000B9534,BfmeStringRecord000B9534>(BfmeStringRecord000B9534*,const BfmeStringRecord000B9534&);
#include <vector>
template class _STL::vector<BfmeStringRecord000B9534, _STL::allocator<BfmeStringRecord000B9534> >;
