// cl: /Ireference/shims/bfme2_ascii /O1 /GX- /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?getScrollFactor@OptionPreferences@@QAEMXZ, retail 0x002E45DA,
// 121 bytes. Dedicated TU.
//
// ZH OptionPreferences::getScrollFactor with three retail-measured
// deviations (miss default is TheGlobalData's keyboard scroll factor float
// at +0xAFC; negatives clamp to 1, not 0; tail multiplies by float-verified
// 0.02f, not /100.0f). Same string plumbing as its siblings.

#include <map>
#include <stdlib.h>
#include <string.h>

typedef bool Bool;
typedef int Int;
typedef float Real;

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
	char m_pad[0xAFC];
	Real m_keyboardDefaultScrollFactor;
};

extern class GlobalData *TheWritableGlobalData;

class OptionPreferences : public AsciiPreferenceMap
{
public:
	virtual ~OptionPreferences();
	Real getScrollFactor();
};

// ?getScrollFactor@OptionPreferences@@QAEMXZ
Real OptionPreferences::getScrollFactor(void)
{
	OptionPreferences::const_iterator it = find("ScrollFactor");
	if (it == end())
		return TheWritableGlobalData->m_keyboardDefaultScrollFactor;

	Int factor = atoi(it->second.str());
	if (factor < 0)
		factor = 1;
	if (factor > 100)
		factor = 100;

	return factor * 0.02f;
}
