// cl: /Ireference/shims/bfme2_ascii /GX- /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?getFirewallPortOverride@OptionPreferences@@QAEGXZ, retail 0x002E48CE,
// 90 bytes. Dedicated TU.
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

class GlobalData
{
public:
	char m_pad[0xA54];
	UnsignedShort m_firewallPortOverride;
};

extern class GlobalData *TheWritableGlobalData;

class OptionPreferences : public AsciiPreferenceMap
{
public:
	virtual ~OptionPreferences();
	UnsignedShort getFirewallPortOverride();
};

// ?getFirewallPortOverride@OptionPreferences@@QAEGXZ
UnsignedShort OptionPreferences::getFirewallPortOverride()
{
	OptionPreferences::const_iterator it = find("FirewallPortOverride");
	if (it == end()) {
		return TheWritableGlobalData->m_firewallPortOverride;
	}

	return atoi(it->second.str());
}
