// cl: /Ireference/shims/bfme2_ascii /GX- /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?getIdealStaticGameDetail@OptionPreferences@@QAEHXZ, retail 0x002E429B,
// 20 bytes, and ?getStaticGameDetail@OptionPreferences@@QAEHXZ, retail
// 0x002E427D, 30 bytes. Dedicated TU.
//
// ZH OptionPreferences::getIdealStaticGameDetail / getStaticGameDetail
// (GeneralsMD/.../OptionsMenu.cpp:409,418) read the LOD level-name table
// at 0xDB95F4 (VeryLow..Custom) through a slot-0x1C virtual taking
// (key, table, count, default); the miss default rides along (-1 for the
// ideal query, the live LOD level at [0xDFE144]+0x1768 for the static
// query). The ideal consumer is the LOD init at 0x202865, which stores
// the result at [esi+0x17C4]. Same vptr+map layout and string plumbing
// as the OptionPreferences getter siblings.

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

// Retail LOD level-name table (VeryLow, Low, Medium, High, UltraHigh,
// Custom) at 0xDB95F4. COMMON merges across TUs; the address patches
// from retail.
extern const char *BfmeLODLevelNames[7];  // defined in OptionPreferences_setStaticGameLOD.cpp

struct Rva00DFE144Globals
{
	char m_pad[0x1768];
	Int m_staticLODLevel;
};

// COMMON merges across TUs; the address patches from retail.
// The global at this VA is TheGameLODManager; this name aliases it rather than
// defining a second variable the rest of the game never sees.
extern class GameLODManager *TheGameLODManager;
#pragma comment(linker, "/alternatename:?TheRva00DFE144@@3PAURva00DFE144Globals@@A=?TheGameLODManager@@3PAVGameLODManager@@A")

class OptionPreferences : public AsciiPreferenceMap
{
public:
	virtual ~OptionPreferences();
	virtual void RvaPad01();
	virtual void RvaPad02();
	virtual void RvaPad03();
	virtual void RvaPad04();
	virtual void RvaPad05();
	virtual void RvaPad06();
	virtual Int GetEnumValue(const char *key, const char *const *table, Int count, Int defaultValue);
	Int getIdealStaticGameDetail();
	Int getStaticGameDetail();
};

// ?getIdealStaticGameDetail@OptionPreferences@@QAEHXZ
Int OptionPreferences::getIdealStaticGameDetail(void)
{
	return GetEnumValue("IdealStaticGameLOD", BfmeLODLevelNames, 6, -1);
}

// ?getStaticGameDetail@OptionPreferences@@QAEHXZ
Int OptionPreferences::getStaticGameDetail(void)
{
	Int level = (*(Rva00DFE144Globals **)&TheGameLODManager)->m_staticLODLevel;
	return GetEnumValue("StaticGameLOD", BfmeLODLevelNames, 6, level);
}
