// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?getLastLadderAddr@CustomMatchPreferences@@QAE?AVAsciiString@@XZ, retail
// 0x005DF4B9, 81 bytes. Dedicated TU.
//
// BFME1 UserPreferences.cpp CustomMatchPreferences::getLastLadderAddr port
// (their matched 98B row). Key mechanism per their source comment: the
// by-value return (hidden retptr, both exits copy-construct) makes the
// compiler null the key slot first (`and [ebp-4],0`), which the
// scalar-returning Port twin lacks. Shaped here as explicit init/destroy
// over a dtor-less shim (their CustomAsciiStringShim, init/destroy alias
// pins) so no EH temp registration outlines the prolog under /EHsc;
// the implicit-conversion temp of the naive spelling does outline it
// (banked 0.95, stash reverse/attempts/0x005df4b9.cpp).
// Claimed under the CustomMatch name because CustomMatchPreferences is the
// class BFME2's own tree proves (WOLGameSetupMenu.cpp) while
// QuickMatchPreferences has no BFME2 presence.

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


// AsciiString::TheEmptyString: defined in Common/Rva00380200Getter.cpp.

struct CustomAsciiStringShim
{
	void *m_data;
	void init(const char *text);
	void destroy();
};

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
	AsciiString getLastLadderAddr();
};

AsciiString CustomMatchPreferences::getLastLadderAddr(void)
{
	CustomAsciiStringShim key;
	key.init("LastLadderAddr");

	CustomMatchPreferences::const_iterator it = find((const AsciiString &)key);
	key.destroy();

	if (it == end()) {
		return AsciiString::TheEmptyString;
	}
	return it->second;
}
