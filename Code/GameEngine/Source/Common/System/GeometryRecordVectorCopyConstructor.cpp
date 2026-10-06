// cl: /Ireference/shims/bfme2_ascii /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Open-BFME: vector<GeometryRecord> copy constructor, retail 0x000FDF90.
// GeometryInfo's copy constructor calls this member through ILT 0x000149DE.

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
	GeometryRecord();
	~GeometryRecord();
	GeometryRecord(const GeometryRecord &other)
		: m_first(other.m_first),
		  m_second(other.m_second),
		  m_third(other.m_third),
		  m_name(other.m_name)
	{
	}
	int m_first;
	int m_second;
	int m_third;
	AsciiString m_name;
};

template class _STL::vector<GeometryRecord>;
