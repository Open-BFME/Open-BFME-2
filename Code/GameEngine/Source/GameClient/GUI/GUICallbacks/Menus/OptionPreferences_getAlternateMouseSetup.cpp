// cl: /Ireference/shims/bfme2_ascii /O1 /GX- /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?getAlternateMouseSetup@OptionPreferences@@QAE_NXZ, retail 0x002E4D4E,
// 96 bytes. Dedicated TU.
//
// ZH OptionPreferences getter shape (GeneralsMD/.../GUICallbacks/Menus/
// OptionsMenu.cpp) via the getTurnOffMessengerInGame twin (same plumbing;
// the miss default is TheGlobalData's byte retail-measured at +0x5C; the
// yes/no test is inverted (`!= 0`, test/setne) calling strcmp through the
// CRT thunk at 0x006291C6, as in BFME1's getAlternateMouseSetup).

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
	char m_pad[0x5C];
	Bool m_alternateMouseSetup;
};

extern class GlobalData *TheWritableGlobalData;

class OptionPreferences : public AsciiPreferenceMap
{
public:
	virtual ~OptionPreferences();
	Bool getAlternateMouseSetup();
};

// ?getAlternateMouseSetup@OptionPreferences@@QAE_NXZ
Bool OptionPreferences::getAlternateMouseSetup(void)
{
	OptionPreferences::const_iterator it = find("AlternateMouseSetup");
	if (it == end())
		return TheWritableGlobalData->m_alternateMouseSetup;

	if (strcmp(it->second.str(), "yes") != 0) {
		return true;
	}
	return false;
}
