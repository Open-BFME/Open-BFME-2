// cl: /Ireference/shims/bfme2_ascii /O1 /GX- /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?getDisplayForeignLanguage@OptionPreferences@@QAE_NXZ, retail 0x002E4E12,
// 100 bytes. Dedicated TU.
//
// ZH OptionPreferences getter shape (GeneralsMD/.../GUICallbacks/Menus/
// OptionsMenu.cpp) via the getTurnOffMessengerInGame twin (same plumbing;
// the miss default is TheGlobalData's byte retail-measured at +0xB6D;
// the yes/no test calls strcmp through the CRT thunk at 0x006291C6).

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
	char m_pad[0xB6D];
	Bool m_displayForeignLanguage;
};

extern class GlobalData *TheWritableGlobalData;

class OptionPreferences : public AsciiPreferenceMap
{
public:
	virtual ~OptionPreferences();
	Bool getDisplayForeignLanguage();
};

// ?getDisplayForeignLanguage@OptionPreferences@@QAE_NXZ
Bool OptionPreferences::getDisplayForeignLanguage(void)
{
	OptionPreferences::const_iterator it = find("DisplayForeignLanguage");
	if (it == end())
		return TheWritableGlobalData->m_displayForeignLanguage;

	if (strcmp(it->second.str(), "yes") == 0) {
		return true;
	}
	return false;
}
