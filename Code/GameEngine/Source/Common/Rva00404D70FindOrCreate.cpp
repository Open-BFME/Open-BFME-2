// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii
// stlport
// ?rva00405684@Rva00404D70@@QAEPAUBfmeStringRecord00404BF3@@ABVAsciiString@@@Z @0x00405684 105B
// Evidence: calls rowed find 0x00404D70 tests 0x7fffffff scales 0x18 from start at +0x120; else ctor row 0x00404BC5 push_back row 0x004055BB releaseBuffer row 0x00036410 returns finish-0x18; caller 0x00215D96 passes AsciiString for initFromINI.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include "ascii_string.h"
#include <vector>

struct BfmeStringRecord00404BF3
{
	AsciiString text;
	float f0;
	float f1;
	float f2;
	float f3;
	float f4;
	BfmeStringRecord00404BF3(const AsciiString &s);
};

class Rva00404D70
{
public:
	int rva00404D70(const AsciiString &s);
	BfmeStringRecord00404BF3 *rva00405684(const AsciiString &s);
private:
	char m_pad[0x120];
	_STL::vector<BfmeStringRecord00404BF3> m_vec;
};

BfmeStringRecord00404BF3 *Rva00404D70::rva00405684(const AsciiString &s)
{
	int idx = rva00404D70(s);
	if (idx != 0x7fffffff)
		return &m_vec[idx];
	m_vec.push_back(BfmeStringRecord00404BF3(s));
	return &m_vec.back();
}
