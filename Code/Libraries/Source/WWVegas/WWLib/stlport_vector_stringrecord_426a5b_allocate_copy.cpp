// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// BFME2's 8-byte BfmeStringRecord00426A5B vector allocation/copy helper at RVA 0x426B46.
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
struct BfmeStringRecord00426A5B {
    AsciiString text;
    unsigned char flag0, flag1, flag2;
    BfmeStringRecord00426A5B();
    BfmeStringRecord00426A5B(const BfmeStringRecord00426A5B &o) : text(o.text), flag0(o.flag0), flag1(o.flag1), flag2(o.flag2) {}
};
#include <memory>
template void _STL::_Construct<BfmeStringRecord00426A5B,BfmeStringRecord00426A5B>(BfmeStringRecord00426A5B*,const BfmeStringRecord00426A5B&);
#include <vector>
template class _STL::vector<BfmeStringRecord00426A5B, _STL::allocator<BfmeStringRecord00426A5B> >;
