// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// ZH UserPreferences.cpp at donor 6583b3c1ff: setMapSelected.
// Native 005DF73F..005DF7A7: two stack arguments, encoded map-name key,
// map at this+4, and literal "1"/"0" value; all string/map callees already rowed.
// QuickMatchPreferences::isMapSelected at 005DF458 uses the same encoded key.

#include <map>

typedef bool Bool;
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

AsciiString AsciiStringToQuotedPrintable(AsciiString original);

class QuickMatchPreferences : public AsciiPreferenceMap
{
public:
	virtual ~QuickMatchPreferences();
	void setMapSelected(const AsciiString &mapName, Bool selected);
};

void QuickMatchPreferences::setMapSelected(const AsciiString &mapName, Bool selected)
{
    (*this)[AsciiStringToQuotedPrintable(mapName)] = selected ? "1" : "0";
}
