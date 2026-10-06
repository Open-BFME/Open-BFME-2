// cl: /Ireference/shims/bfme2_ascii /GX- /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?getTurnOffMessengerInGame@OptionPreferences@@QAE_NXZ, retail 0x002E4C2B,
// 100 bytes. Dedicated TU.
//
// ZH OptionPreferences getter shape (GeneralsMD/.../GUICallbacks/Menus/
// OptionsMenu.cpp) via the getSendDelay twin (same plumbing; the miss default
// is TheGlobalData's byte retail-measured at +0xB69).

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

class GlobalData
{
public:
	char m_pad[0xB69];
	Bool m_turnOffMessengerInGame;
};

extern class GlobalData *TheWritableGlobalData;

class OptionPreferences : public AsciiPreferenceMap
{
public:
	virtual ~OptionPreferences();
	Bool getTurnOffMessengerInGame();
};

// ?getTurnOffMessengerInGame@OptionPreferences@@QAE_NXZ
Bool OptionPreferences::getTurnOffMessengerInGame(void)
{
	OptionPreferences::const_iterator it = find("TurnOffMessengerInGame");
	if (it == end())
		return TheWritableGlobalData->m_turnOffMessengerInGame;

	if (strcmp(it->second.str(), "yes") == 0) {
		return true;
	}
	return false;
}
