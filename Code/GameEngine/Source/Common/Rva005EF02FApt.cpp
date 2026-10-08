// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// StrategicHUD::SetArmyNameString retail 0x005EF02F 103B (WorldBuilder name,
// StrategicHUDRegionDetailsArmiesMovieClip.cpp; same _ArmyName key and SetText)
// Evidence: format APT:_level%u.%s_ArmyName via 0x00038150; bfmeSetText via pin 0x00225301; releaseBuffer 0x00036410; globals 0x009FE4CC 0x007BAC1C; callers 0x005EF576 0x005EFAD0; precedent Rva005FDF1CApt.cpp
template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


#include "unicode_string.h"

struct Rva005EF02FInner
{
	char m_pad8[8];
	char m_name[1];
};

struct Rva005EF02FOuter
{
	Rva005EF02FInner *m_ptr;
};

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &, const UnicodeString &, bool);
};

class Rva00222A8BTarget
{
};

extern Rva00222A8BTarget *TheRva00222A8BTarget;

namespace StrategicHUD
{
	void SetArmyNameString(int level, Rva005EF02FOuter *outer, const UnicodeString &text);
}

void StrategicHUD::SetArmyNameString(int level, Rva005EF02FOuter *outer, const UnicodeString &text)
{
	AsciiString key;
	const char *mid = outer->m_ptr ? outer->m_ptr->m_name : "";
	key.format("APT:_level%u.%s_ArmyName", level, mid);
	((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, text, true);
}
