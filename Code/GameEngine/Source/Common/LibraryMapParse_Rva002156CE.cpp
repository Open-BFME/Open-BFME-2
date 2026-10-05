// cl: -DNDEBUG -MD -EHsc /Os -Ireference/shims/bfme2_ascii -Ireference/open-bfme-1/game/GameEngine/Source/Common
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

#include <vector>
#include "ascii_string.h"

class INI
{
public:
	AsciiString getNextQuotedAsciiString();
};

class LibraryMap
{
public:
	static void parse(INI *ini, void *instance, void *store,
		const void *userData);

private:
	AsciiString m_name;
	// The donor spells this element Open2Elem063700, a same-layout string
	// wrapper whose copy and destructor are the AsciiString ones; retail's
	// push_back at 0x0002DBE6 is the shared vector<AsciiString> body, so the
	// element is spelled AsciiString here and the call resolves directly.
	std::vector<AsciiString> m_libraryMaps;
};

void LibraryMap::parse(INI *ini, void *instance, void *store, const void *userData)
{
	((LibraryMap *)instance)->m_libraryMaps.push_back(ini->getNextQuotedAsciiString());
}
