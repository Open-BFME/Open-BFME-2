// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?setUsesLongGameList@CustomMatchPreferences@@QAEX_N@Z, retail 0x0054F745,
// 120 bytes. Dedicated TU.
//
// ZH CustomMatchPreferences::setUsesLongGameList verbatim shape (format the
// Bool with "%d", then assign through the prefs map) with the named-key
// plus named-slot split from the landed setter siblings so the text push
// sinks below the op[] call. Same string plumbing with pinned
// operator[]/assign/ctor/release/format callees. Retail keeps default EH.

#include <map>

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

namespace _STL
{
template <> AsciiString &map<AsciiString, AsciiString, less<AsciiString>, allocator<pair<const AsciiString, AsciiString> > >::operator[](const AsciiString &key);
}

class CustomMatchPreferences : public AsciiPreferenceMap
{
public:
	virtual ~CustomMatchPreferences();
	void setUsesLongGameList(Bool val);
};

// ?setUsesLongGameList@CustomMatchPreferences@@QAEX_N@Z
void CustomMatchPreferences::setUsesLongGameList(Bool val)
{
	AsciiString strVal;
	strVal.format("%d", val);
	AsciiString key("UseLongGameList");
	AsciiString &slot = (*this)[key];
	slot = strVal;
}
