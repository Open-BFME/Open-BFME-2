// cl: /Ireference/shims/bfme2_ascii /GX- /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?getDisallowNonAsianText@CustomMatchPreferences@@QAE_NXZ, retail 0x0054F63A,
// 92 bytes. Dedicated TU.
//
// ZH/BFME1 CustomMatchPreferences::getDisallowNonAsianText verbatim shape
// (BFME1 matches it as clean C++); raw stricmp against "1" rather than the
// compareNoCase method the sibling bool getters use. Same string plumbing
// as the OptionPreferences family: TU-local StringBase/AsciiString, real
// STLport map (find worker pinned), StringBase ctor and releaseBuffer
// pinned, stricmp via import.

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

class CustomMatchPreferences : public AsciiPreferenceMap
{
public:
	virtual ~CustomMatchPreferences();
	Bool getDisallowNonAsianText();
};

Bool CustomMatchPreferences::getDisallowNonAsianText(void)
{
	CustomMatchPreferences::const_iterator it = find("DisallowNonAsianText");
	if (it == end())
		return false;

	register Bool match = (_strcmpi(it->second.str(), "1") == 0);
	return match;
}
