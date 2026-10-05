// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport

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

#include "ascii_string.h"

namespace rts
{
	template <class T> struct hash
	{
	};
	template <> struct hash<AsciiString>
	{
		unsigned int operator()(const AsciiString &key) const;
	};
}

#include <hash_map>
#include <set>

class INIMacroTable
{
public:
	INIMacroTable();

private:
	std::hash_map<AsciiString, AsciiString, rts::hash<AsciiString>, std::equal_to<AsciiString> > m_macros;
	std::set<AsciiString> m_expanded;
	void *m_unkn20;
	void *m_unkn24;
};

INIMacroTable::INIMacroTable()
	: m_macros()
	, m_expanded()
	, m_unkn20(0)
	, m_unkn24(0)
{
}
