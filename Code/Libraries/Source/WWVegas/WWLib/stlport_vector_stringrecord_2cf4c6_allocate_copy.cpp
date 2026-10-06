// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// BFME2's 20-byte BfmeStringRecord002CF4C6 vector allocation/copy helper at RVA 0x2CFC4E.
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
struct BfmeStringRecord002CF4C6 {
    AsciiString text0, text1;
    unsigned int word0, word1;
    unsigned char flag0, flag1;
    BfmeStringRecord002CF4C6();
    BfmeStringRecord002CF4C6(const BfmeStringRecord002CF4C6 &o) : text0(o.text0), text1(o.text1), word0(o.word0), word1(o.word1), flag0(o.flag0), flag1(o.flag1) {}
};
#include <memory>
template void _STL::_Construct<BfmeStringRecord002CF4C6,BfmeStringRecord002CF4C6>(BfmeStringRecord002CF4C6*,const BfmeStringRecord002CF4C6&);
#include <vector>
template class _STL::vector<BfmeStringRecord002CF4C6, _STL::allocator<BfmeStringRecord002CF4C6> >;
