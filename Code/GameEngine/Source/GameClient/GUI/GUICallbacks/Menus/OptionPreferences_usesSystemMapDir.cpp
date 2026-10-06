// cl: /Ireference/shims/bfme2_ascii /GX- /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?usesSystemMapDir@OptionPreferences@@QAE_NXZ, retail 0x002E4653,
// 92 bytes. Dedicated TU.
//
// ZH OptionPreferences::usesSystemMapDir verbatim
// (GeneralsMD/.../GUICallbacks/Menus/OptionsMenu.cpp). Same string plumbing
// as OptionPreferences_saveCameraInReplays.cpp (AptMap stand-ins, real
// STLport map, _M_find pinned); the yes/no test calls the msvcr71 _strcmpi
// import (proven by the BitFlags getSingleBitFromName family to live at
// 0x00BBA518) via <string.h>.

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
	Bool usesSystemMapDir();
};

// ?usesSystemMapDir@OptionPreferences@@QAE_NXZ
Bool OptionPreferences::usesSystemMapDir(void)
{
	OptionPreferences::const_iterator it = find("UseSystemMapDir");
	if (it == end())
		return true;

	if (_strcmpi(it->second.str(), "yes") == 0) {
		return true;
	}
	return false;
}
