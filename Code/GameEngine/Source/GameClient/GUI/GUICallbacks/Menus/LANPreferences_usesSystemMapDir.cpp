// cl: /Ireference/shims/bfme2_ascii /GX- /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?usesSystemMapDir@LANPreferences@@QAE_NXZ, retail 0x0043C32A,
// 90 bytes. Dedicated TU.
//
// ZH LANPreferences::usesSystemMapDir verbatim shape
// (GeneralsMD/.../LanLobbyMenu.cpp:148: miss returns TRUE, compares the
// stored value case-insensitively against "yes"). Same string plumbing
// as the OptionPreferences family: TU-local StringBase/AsciiString, real
// STLport map (find worker pinned at 0x1F8437), StringBase ctor and
// releaseBuffer pinned, _strcmpi via import (slot 0xBBA518).
//
// The key temporary is built by a LANPreferences helper (pinned opaquely
// at 0x43BB6A, 7 same-cluster callers) that returns the key AsciiString
// by value: the hidden return pointer rides the stack under the literal,
// so the call reads push-literal/push-temp and find takes the returned
// eax. Probe-proven byte-identical on the first spelling.

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

class LANPreferences : public AsciiPreferenceMap
{
public:
	virtual ~LANPreferences();
	Bool usesSystemMapDir();
};

class SkirmishPreferences
{
public:
	AsciiString buildProfileKey(const char *src);
};

Bool LANPreferences::usesSystemMapDir(void)
{
	LANPreferences::const_iterator it = find(
		((SkirmishPreferences *)this)->buildProfileKey("UseSystemMapDir"));
	if (it == end())
		return true;

	register Bool match = (_strcmpi(it->second.str(), "yes") == 0);
	return match;
}
