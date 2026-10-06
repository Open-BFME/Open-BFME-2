// cl: /Ireference/shims/bfme2_ascii /GX- /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?getMaxPing@QuickMatchPreferences@@QAEHXZ, retail 0x005DF6EE, 81 bytes.
// Dedicated TU.
//
// ZH QuickMatchPreferences::getMaxPing shape, except BFME2 returns -1 (not
// 5) when the key is missing. Same string plumbing as the OptionPreferences
// family: TU-local StringBase/AsciiString, real STLport map (find worker
// pinned), StringBase ctor and releaseBuffer pinned, atoi via import.

#include <map>
#include <stdlib.h>

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

class QuickMatchPreferences : public AsciiPreferenceMap
{
public:
	virtual ~QuickMatchPreferences();
	Int getMaxPing();
};

Int QuickMatchPreferences::getMaxPing(void)
{
	QuickMatchPreferences::const_iterator it = find("MaxPing");
	if (it == end()) {
		return -1;
	}
	return atoi(it->second.str());
}
