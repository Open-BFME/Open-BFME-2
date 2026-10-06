// cl: /Ireference/shims/bfme2_ascii /GX- /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?getFirewallNeedToRefresh@OptionPreferences@@QAE_NXZ, retail 0x002E4928,
// 103 bytes. Dedicated TU.
//
// ZH OptionPreferences::getFirewallNeedToRefresh verbatim. Same string
// plumbing as its siblings, plus the AsciiString copy ctor (pinned) and the
// StringBase compareNoCase import (already pinned).

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

class OptionPreferences : public AsciiPreferenceMap
{
public:
	virtual ~OptionPreferences();
	Bool getFirewallNeedToRefresh();
};

// ?getFirewallNeedToRefresh@OptionPreferences@@QAE_NXZ
Bool OptionPreferences::getFirewallNeedToRefresh()
{
	OptionPreferences::const_iterator it = find("FirewallNeedToRefresh");
	if (it == end()) {
		return false;
	}

	Bool retval = false;
	AsciiString str = it->second;
	if (((const StringBase<char> &)str).compareNoCase("TRUE") == 0) {
		retval = true;
	}
	return retval;
}
