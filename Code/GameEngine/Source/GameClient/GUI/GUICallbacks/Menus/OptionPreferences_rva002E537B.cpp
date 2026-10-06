// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?rva002E537B@OptionPreferences@@QAEXH@Z, retail 0x002E537B,
// 127 bytes. Dedicated TU.
//
// IdealStaticGameLOD twin of rva002E52FC: -1 erases the key via rowed
// string-tree erase 0x002E4ED1, else writes BfmeLODLevelNames[val] through
// base-map subscript 0x002031FB plus StringBase::set 0x000055F5; key at
// 0x804D1C, table at 0xDB95F4 shared with getStaticGameDetail.

#include <map>
#include <stdlib.h>
#include <string.h>

typedef bool Bool;
typedef int Int;

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
template <> unsigned int _Rb_tree<AsciiString, pair<const AsciiString, AsciiString>, _Select1st<pair<const AsciiString, AsciiString> >, less<AsciiString>, allocator<pair<const AsciiString, AsciiString> > >::erase(const AsciiString &key);
}

// Retail LOD level-name table at 0xDB95F4, defined in
// OptionPreferences_getStaticGameDetail.cpp; this TU only references it.
extern const char *BfmeLODLevelNames[];

class OptionPreferences : public AsciiPreferenceMap
{
public:
	virtual ~OptionPreferences();
	void rva002E537B(Int val);
};

void OptionPreferences::rva002E537B(Int val)
{
	if (val != -1) {
		AsciiString key("IdealStaticGameLOD");
		// Retail loads the name before the map call and retains it in EDI.
		const char *levelName = BfmeLODLevelNames[val];
		AsciiString &value = (*this)[key];
		value.set(levelName);
	} else {
		erase(AsciiString("IdealStaticGameLOD"));
	}
}
