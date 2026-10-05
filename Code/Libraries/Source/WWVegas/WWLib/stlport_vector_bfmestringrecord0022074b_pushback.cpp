// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?push_back@?$vector@UBfmeStringRecord0022074B@@V?$allocator@UBfmeStringRecord0022074B@@@_STL@@@_STL@@QAEXABUBfmeStringRecord0022074B@@@Z @0x00220F8D 55B
// STLport vector<BfmeStringRecord0022074B>::push_back fast path via rowed
// _Construct 0x0022088B else rowed _M_insert_overflow 0x00220EBA with n=1.
// Same 55B shape as UnicodeString push_back 0x0005CBE7. Evidence: unlock lane
// missing callee of 0x00220FC4, retail cmp je Construct add 0x0C vs overflow,
// caller 0x00220FF5, neighbours 0x00220F71/0x00221027.
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

#include <vector>

class AsciiString
{
public:
	AsciiString();
	AsciiString(const AsciiString &other);
	~AsciiString();
	AsciiString &operator=(const AsciiString &other);
private:
	void *m_data;
};

struct BfmeStringRecord0022074B
{
	AsciiString text0;
	AsciiString text1;
	unsigned int word;
	BfmeStringRecord0022074B(const BfmeStringRecord0022074B &other);
};

namespace _STL
{
template <> void _Construct<BfmeStringRecord0022074B, BfmeStringRecord0022074B>(BfmeStringRecord0022074B *, const BfmeStringRecord0022074B &);
}

template void _STL::vector<BfmeStringRecord0022074B>::push_back(const BfmeStringRecord0022074B &);
