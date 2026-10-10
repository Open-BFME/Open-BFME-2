// cl: -DNDEBUG -MD -EHsc -Ireference/shims/bfme2_ascii -Ireference/open-bfme-1/game/GameEngine/Source/Common
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
