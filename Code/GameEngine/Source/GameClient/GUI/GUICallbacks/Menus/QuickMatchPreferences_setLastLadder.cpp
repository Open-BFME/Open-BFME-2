// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?setLastLadder@QuickMatchPreferences@@QAEXABVAsciiString@@G@Z, retail
// 0x005DF7A7, 175 bytes. Dedicated TU.
//
// ZH/BFME1 QuickMatchPreferences::setLastLadder verbatim shape (port
// formatted with "%d", then LastLadderAddr and LastLadderPort assigned
// through the prefs map) with the named-key plus named-slot split from the
// landed OptionPreferences setters so each value push sinks below its op[]
// call. Scoped keys share the dead port-param slot. Class proven by the
// shared-object caller at 0x5BA499 which drives this body and the
// QuickMatch-only int setters on one prefs local (ZH CustomMatch has no int
// setters). Same string plumbing with pinned operator[]/assign/ctor/
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

class QuickMatchPreferences : public AsciiPreferenceMap
{
public:
	virtual ~QuickMatchPreferences();
	void setLastLadder(const AsciiString &addr, UnsignedShort port);
};

// ?setLastLadder@QuickMatchPreferences@@QAEXABVAsciiString@@G@Z
void QuickMatchPreferences::setLastLadder(const AsciiString &addr, UnsignedShort port)
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
