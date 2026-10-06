// cl: /Ireference/shims/bfme2_ascii /GX- /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?getBrightness@OptionPreferences@@QAEMXZ, retail 0x002E4A47,
// 90 bytes. Dedicated TU.
//
// BFME1 OptionPreferences::getBrightness verbatim
// (reference/open-bfme-1 Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/R4OptionPreferencesBoolGetters.cpp:
// key "Brightness", miss-50.0f, (float)atoi of the stored text). Same string
// plumbing as OptionPreferences_hasSeenLogoMovies.cpp (TU-local
// StringBase/AsciiString, real STLport map with the 0x1F8437 find worker
// pinned, StringBase ctor and releaseBuffer pinned, atoi via <stdlib.h> to
// the msvcr71 slot 0x00BBA624).

#include <map>
#include <stdlib.h>
#include <string.h>

typedef bool Bool;
typedef int Int;

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};
}

typedef _STL::map<AsciiString, AsciiString> AsciiPreferenceMap;

class OptionPreferences : public AsciiPreferenceMap
{
public:
	virtual ~OptionPreferences();
	float getBrightness();
};

float OptionPreferences::getBrightness(void)
{
	OptionPreferences::const_iterator it = find("Brightness");
	if (it == end())
		return 50.0f;

	float brightness = (float)atoi(it->second.str());
	return brightness;
}
