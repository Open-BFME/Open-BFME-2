// cl: /Ireference/shims/bfme2_ascii /GX- /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?getFirewallPortAllocationDelta@OptionPreferences@@QAEFXZ, retail 0x002E4874,
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
typedef short Short;

#include "../../../../../Include/Common/BfmeStringData.h"

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

#include "../../../../../Include/Common/GlobalData.h"

extern class GlobalData *TheWritableGlobalData;

#include "../../../../../Include/Common/OptionPreferences.h"

// ?getFirewallPortAllocationDelta@OptionPreferences@@QAEFXZ
Short OptionPreferences::getFirewallPortAllocationDelta()
{
	OptionPreferences::const_iterator it = find("FirewallPortAllocationDelta");
	if (it == end()) {
		return TheWritableGlobalData->m_firewallPortAllocationDelta;
	}

	Short delta = atoi(it->second.str());
	return delta;
}
