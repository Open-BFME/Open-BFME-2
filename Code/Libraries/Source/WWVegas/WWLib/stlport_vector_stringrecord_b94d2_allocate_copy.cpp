// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// BFME2's 8-byte BfmeStringRecord000B94D2 vector allocation/copy helper at RVA 0xBC72B.
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
struct BfmeStringRecord000B94D2 {
    AsciiString text0, text1;
    BfmeStringRecord000B94D2();
    BfmeStringRecord000B94D2(const BfmeStringRecord000B94D2 &o) : text0(o.text0), text1(o.text1) {}
};
#include <memory>
template void _STL::_Construct<BfmeStringRecord000B94D2,BfmeStringRecord000B94D2>(BfmeStringRecord000B94D2*,const BfmeStringRecord000B94D2&);
#include <vector>
template class _STL::vector<BfmeStringRecord000B94D2, _STL::allocator<BfmeStringRecord000B94D2> >;
