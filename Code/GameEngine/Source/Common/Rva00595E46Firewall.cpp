// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?Rva00595E46Save@@YAXXZ @0x00595E46 314B evidence: FirewallBehavior 0x7EB734 plus FirewallPortAllocationDelta 0x7EB700 strings via OptionPreferences map plus TheWritableGlobalData firewallBehavior+0xA4C and delta+0xA58 via g_a063b0 plus UserPreferences write; callers 0x00518324 0x00519CCC 0x005700D4
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

class GlobalData
{
public:
	char m_pad[0xA4C];
	Int m_firewallBehavior;
	char m_pad2[0xA58 - 0xA4C - 4];
	Short m_firewallPortAllocationDelta;
};

extern GlobalData *TheWritableGlobalData;

struct Rva00A063B0Obj
{
	void *m_vtbl;
	Int m_04;
	char m_pad08[4];
	Short m_0C;
	char m_pad0E[0x17C - 0x0E];
	Int m_17C;
};

extern struct Rva00A063B0Obj *g_a063b0;

extern "C" __declspec(dllimport) char *__cdecl _itoa(int value, char *buffer, int radix);

void Rva00595E46Save(void)
{
	OptionPreferences prefs;
	Rva00A063B0Obj *info = g_a063b0;
	char num[16];
	num[0] = 0;
	info->m_17C = 0;
	TheWritableGlobalData->m_firewallBehavior = info->m_04;
	_itoa(TheWritableGlobalData->m_firewallBehavior, num, 10);
	AsciiString numstr;
	numstr = num;
	{
		AsciiString key("FirewallBehavior");
		AsciiString &slot = prefs[key];
		slot = numstr;
	}
	TheWritableGlobalData->m_firewallPortAllocationDelta = g_a063b0->m_0C;
	num[0] = 0;
	_itoa(TheWritableGlobalData->m_firewallPortAllocationDelta, num, 10);
	numstr = num;
	{
		AsciiString key("FirewallPortAllocationDelta");
		AsciiString &slot = prefs[key];
		slot = numstr;
	}
	prefs.write();
}

// Native OptionPreferences table C04CE8 slot0 -> deleting body2E42D2
// -> complete destructor2E4272. Keep this binding separate from the local view.
#pragma comment(linker, "/alternatename:??1OptionPreferences@@UAE@XZ=??1Rva002E4272@@UAE@XZ")
