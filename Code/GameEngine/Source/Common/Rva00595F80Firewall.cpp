// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?flagNeedToRefresh@FirewallHelperClass@@QAEX_N@Z @0x00595F80 215B evidence: ZH FirewallHelper.cpp plus BFME1 same with TRUE FALSE FirewallNeedToRefresh strings via OptionPreferences write; callers 0x005700E0 0x005A899B pass this plus bool; donor void flagNeedToRefresh(Bool)
#include <map>
#include <stdlib.h>

typedef bool Bool;
typedef int Int;
typedef short Short;

#include "ascii_string.h"
#include "unicode_string.h"

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

typedef _STL::map<AsciiString, AsciiString> PreferenceMap;

namespace _STL
{
template <> AsciiString &map<AsciiString, AsciiString, less<AsciiString>, allocator<pair<const AsciiString, AsciiString> > >::operator[](const AsciiString &key);
}

class UserPreferences : public PreferenceMap
{
public:
	UserPreferences();
	virtual ~UserPreferences();
	virtual Bool write(void);
protected:
	UnicodeString m_filename;
};

class Rva002E4272 : public UserPreferences
{
public:
	virtual ~Rva002E4272();
};

class OptionPreferences : public Rva002E4272
{
public:
	OptionPreferences();
	virtual ~OptionPreferences();
};

class FirewallHelperClass
{
public:
	void flagNeedToRefresh(Bool flag);
};

void FirewallHelperClass::flagNeedToRefresh(Bool flag)
{
	OptionPreferences prefs;
	(prefs)["FirewallNeedToRefresh"].setCopyInline(flag ? AsciiString("TRUE") : AsciiString("FALSE"));
	prefs.write();
}

// Native OptionPreferences table C04CE8 slot0 -> deleting body2E42D2
// -> complete destructor2E4272. Keep this binding separate from the local view.
#pragma comment(linker, "/alternatename:??1OptionPreferences@@UAE@XZ=??1Rva002E4272@@UAE@XZ")
