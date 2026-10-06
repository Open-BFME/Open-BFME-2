// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?setLastLadder@CustomMatchPreferences@@QAEXABVAsciiString@@G@Z, retail
// 0x0054F696, 175 bytes. Dedicated TU.
//
// ZH/BFME1 CustomMatchPreferences::setLastLadder verbatim shape (port
// formatted with "%d", then LastLadderAddr and LastLadderPort assigned
// through the prefs map) with the named-key plus named-slot split from the
// landed OptionPreferences setters so each value push sinks below its op[]
// call. Scoped keys share the dead port-param slot. Second of the two
// setLastLadder twins (the other at 0x5DF7A7 is QuickMatch's per the
// shared-object caller evidence); sits among the CustomMatch Asian-flag
// getters. Same string plumbing with pinned operator[]/assign/ctor/
// release/format callees. Retail keeps default EH (three live temps).

#include <map>

typedef bool Bool;
typedef int Int;
typedef unsigned short UnsignedShort;

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
	void setLastLadder(const AsciiString &addr, UnsignedShort port);
};

// ?setLastLadder@CustomMatchPreferences@@QAEXABVAsciiString@@G@Z
void CustomMatchPreferences::setLastLadder(const AsciiString &addr, UnsignedShort port)
{
	AsciiString strVal;
	strVal.format("%d", port);
	{
		AsciiString key("LastLadderAddr");
		AsciiString &slot = (*this)[key];
		slot = addr;
	}
	{
		AsciiString key("LastLadderPort");
		AsciiString &slot = (*this)[key];
		slot = strVal;
	}
}
