// cl: /Ireference/shims/bfme2_ascii /O1 /GX- /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?getResolution@OptionPreferences@@QAEXPAH0@Z, retail 0x002E4AA1,
// 140 bytes. Dedicated TU.
//
// ZH OptionPreferences::getScrollFactor with three retail-measured
// deviations (miss default is TheGlobalData's keyboard scroll factor float
// at +0xAFC; negatives clamp to 1, not 0; tail multiplies by float-verified
// 0.02f, not /100.0f). Same string plumbing as its siblings.

#include <map>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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
	char m_pad[0x30];
	Int m_xResolution;
	Int m_yResolution;
};

extern class GlobalData *TheWritableGlobalData;

class OptionPreferences : public AsciiPreferenceMap
{
public:
	virtual ~OptionPreferences();
	void getResolution(Int *xres, Int *yres);
};

// ?getResolution@OptionPreferences@@QAEXPAH0@Z
void OptionPreferences::getResolution(Int *xres, Int *yres)
{
	*xres = TheWritableGlobalData->m_xResolution;
	*yres = TheWritableGlobalData->m_yResolution;

	OptionPreferences::const_iterator it = find("Resolution");
	if (it == end())
		return;

	Int selectedXRes,selectedYRes;
	if (sscanf(it->second.str(),"%d%d", &selectedXRes, &selectedYRes) != 2)
		return;

	*xres=selectedXRes;
	*yres=selectedYRes;
}
