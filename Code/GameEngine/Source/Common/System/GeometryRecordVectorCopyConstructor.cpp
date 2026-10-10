// cl: /Ireference/shims/bfme2_ascii /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Open-BFME: vector<GeometryRecord> copy constructor, retail 0x000FDF90.
// GeometryInfo's copy constructor calls this member through ILT 0x000149DE.

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
