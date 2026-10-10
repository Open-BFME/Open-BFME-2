// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport

// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

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
