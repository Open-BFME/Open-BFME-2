// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// BFME2 20-byte BfmeStringRecord00204A30 vector helpers (word AsciiString word AsciiString word = 0x14).
// ??$_Destroy@PAUBfmeStringRecord00204A30@@@_STL@@YAXPAUBfmeStringRecord00204A30@@0@Z retail 0x00206CBA 25B via dtor 0x00204848.
// ??$__copy@PAUBfmeStringRecord00204A30@@PAU1@H@_STL@@YAPAUBfmeStringRecord00204A30@@PAU1@00ABUrandom_access_iterator_tag@0@PAH@Z retail 0x00204170 50B via assign 0x00203DDA.
// ??$__copy_ptrs@PAUBfmeStringRecord00204A30@@PAU1@@_STL@@YAPAUBfmeStringRecord00204A30@@PAU1@00U__false_type@0@@Z retail 0x00204A13 29B via __copy 0x00204170.
// Layout matches the 0x00204A30 copy ctor; callers are vector erase paths 0x00207F40 and 0x00357CA2.
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

class AsciiString { public: AsciiString(const AsciiString &); AsciiString &operator=(const AsciiString &); __forceinline ~AsciiString() { releaseBuffer(); } protected: void releaseBuffer(); private: void *m_data; };
#include <vector>
struct BfmeStringRecord00204A30 {
    unsigned int word0; AsciiString text0; unsigned int word1; AsciiString text1; unsigned int word2;
    BfmeStringRecord00204A30();
    BfmeStringRecord00204A30(const BfmeStringRecord00204A30 &);
    ~BfmeStringRecord00204A30();
    BfmeStringRecord00204A30 &operator=(const BfmeStringRecord00204A30 &);
};
namespace _STL {
template <> void _Construct<BfmeStringRecord00204A30, BfmeStringRecord00204A30>(BfmeStringRecord00204A30 *, const BfmeStringRecord00204A30 &);
}
template class _STL::vector<BfmeStringRecord00204A30, _STL::allocator<BfmeStringRecord00204A30> >;

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1Rva00207E65Vector@@QAE@XZ=??1?$vector@UBfmeStringRecord00204A30@@V?$allocator@UBfmeStringRecord00204A30@@@_STL@@@_STL@@QAE@XZ")
