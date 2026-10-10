// cl: /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME: canonical GeometryRecord vector specialization used by the
// GeometryInfo constructor at retail 0x00100580.
//
// The exact constructor supplies vector<GeometryRecord>'s +0x38 owner and
// calls erase through ILT 0x0001BD38.  The thunk routes to the 76-byte body at
// 0x000FF890.  Its 0x10-byte stride agrees with GeometryRecord's three scalar
// fields and one-pointer AsciiString member.

// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

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
