// cl: /Ireference/shims/bfme2_ascii /O1 /GX- /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?getLanguageFilter@OptionPreferences@@QAE_NXZ, retail 0x002E4BC7,
// 100 bytes. Dedicated TU.
//
// ZH OptionPreferences::getSendDelay verbatim
// (GeneralsMD/.../GUICallbacks/Menus/OptionsMenu.cpp:427). Same string
// plumbing as its siblings; the miss default is TheGlobalData's firewall
// send-delay byte (retail-measured at +0xA50).

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
	char m_pad[0xB68];
	Bool m_languageFilter;
};

int strcmp(const char *a, const char *b);

extern class GlobalData *TheWritableGlobalData;

class OptionPreferences : public AsciiPreferenceMap
{
public:
	virtual ~OptionPreferences();
	Bool getLanguageFilter();
};

// ?getLanguageFilter@OptionPreferences@@QAE_NXZ
Bool OptionPreferences::getLanguageFilter(void)
{
	OptionPreferences::const_iterator it = find("LanguageFilter");
	if (it == end())
		return TheWritableGlobalData->m_languageFilter;

	if (strcmp(it->second.str(), "yes") == 0) {
		return true;
	}
	return false;
}
