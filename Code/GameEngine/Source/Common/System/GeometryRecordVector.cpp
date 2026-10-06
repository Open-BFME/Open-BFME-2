// cl: /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME: canonical GeometryRecord vector specialization used by the
// GeometryInfo constructor at retail 0x00100580.
//
// The exact constructor supplies vector<GeometryRecord>'s +0x38 owner and
// calls erase through ILT 0x0001BD38.  The thunk routes to the 76-byte body at
// 0x000FF890.  Its 0x10-byte stride agrees with GeometryRecord's three scalar
// fields and one-pointer AsciiString member.

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

#include "ascii_string.h"

struct GeometryRecord
{
	~GeometryRecord();
	int m_first;
	int m_second;
	int m_third;
	AsciiString m_name;
};

template class _STL::vector<GeometryRecord>;
