// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii
// stlport
// ?rva00405684@Rva00404D70@@QAEPAUBfmeStringRecord00404BF3@@ABVAsciiString@@@Z @0x00405684 105B
// Evidence: calls rowed find 0x00404D70 tests 0x7fffffff scales 0x18 from start at +0x120; else ctor row 0x00404BC5 push_back row 0x004055BB releaseBuffer row 0x00036410 returns finish-0x18; caller 0x00215D96 passes AsciiString for initFromINI.
// The retail provider calls the established record-vector push_back55B
// at4055BB; this TU needs only its declaration and the native three-pointer
// indexed/back accessors. Importing vector's unused growth machinery emitted
// allocator/cleanup copies that diverged from the existing kept providers.
// The real STLport header provides the three-pointer vector; push_back stays a
// declaration bound to the kept provider.
#include <vector>
#include "ascii_string.h"
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

namespace _STL {
template <> void vector<BfmeStringRecord00404BF3>::push_back(const BfmeStringRecord00404BF3 &);
}

class Rva00404D70
{
public:
	int rva00404D70(const AsciiString &s);
	BfmeStringRecord00404BF3 *rva00405684(const AsciiString &s);
private:
	char m_pad[0x120];
	_STL::vector<BfmeStringRecord00404BF3> m_vec;
};

BfmeStringRecord00404BF3 *Rva00404D70::rva00405684(const AsciiString &asciiString)
{
	int idx = rva00404D70(asciiString);
	if (idx != 0x7fffffff)
		return &m_vec[idx];
	m_vec.push_back(BfmeStringRecord00404BF3(asciiString));
	return &m_vec.back();
}
