// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?setNumPlayers@QuickMatchPreferences@@QAEXH@Z, retail 0x005DFA3A,
// 121 bytes. Dedicated TU.
//
// ZH QuickMatchPreferences::setNumPlayers shape (format plus map assign)
// with the named-key plus named-slot split from the landed setCampaign
// sibling so the text push sinks below the op[] call. Same string plumbing
// with pinned operator[]/assign/ctor/release/format callees. Retail keeps
// default EH.

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

class QuickMatchPreferences : public AsciiPreferenceMap
{
public:
	virtual ~QuickMatchPreferences();
	void setNumPlayers(Int value);
};

// ?setNumPlayers@QuickMatchPreferences@@QAEXH@Z
void QuickMatchPreferences::setNumPlayers(Int value)
{
	AsciiString strVal;
	strVal.format("%d", value);
	AsciiString key("NumPlayers");
	AsciiString &slot = (*this)[key];
	slot = strVal;
}
