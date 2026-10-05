// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// BFME2's 20-byte BfmeStringRecord00568CE0 vector allocation/copy helper at RVA 0x56930C.
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
struct BfmeStringRecord00568CE0 {
    AsciiString text0, text1;
    unsigned int word0, word1;
    unsigned char flag;
    BfmeStringRecord00568CE0();
    BfmeStringRecord00568CE0(const BfmeStringRecord00568CE0 &o);
};
#include <memory>
namespace _STL {
template <> void _Construct<BfmeStringRecord00568CE0, BfmeStringRecord00568CE0>(
	BfmeStringRecord00568CE0 *, const BfmeStringRecord00568CE0 &);
}
#include <vector>
namespace _STL {
template <> BfmeStringRecord00568CE0 *allocator<BfmeStringRecord00568CE0>::allocate(unsigned int, const void *) const;
}
template class _STL::vector<BfmeStringRecord00568CE0, _STL::allocator<BfmeStringRecord00568CE0> >;
