// cl: /MD /EHsc
// ?SetCommandPointsString@StrategicHUD@@YAXHPAURva005EF096Outer@@HH@Z retail 0x005EF096 207B
// Evidence: TheGameText fetch slot 0x3C STRATEGICHUD:StatsCommandPoints; Unicode format 0x006CB5D0 with +8-or-NullChr; Ascii format APT:_level%u.%s_CommandPoints; bfmeSetText pin 0x00225301; globals 0x009FF0BC 0x009FE4CC 0x007BAC1C 0x007BB5C4; callers 0x005EF2DD 0x005EFADE; precedent Rva005D38C8Fetch.cpp plus Rva005FDF1CApt.cpp
struct Rva005EF096Outer;
namespace StrategicHUD
{
	void __cdecl SetCommandPointsString(int level, Rva005EF096Outer *outer, int a, int b);
}
typedef unsigned short wchar_t;
typedef bool Bool;

template <typename T> class StringBase;
class UnicodeString;
class AsciiString;

// The public narrow teardown spelling (declared out of line by this switch)
// resolves to the verified 133-byte releaseBuffer worker at RVA 0x36410.
// Wide teardown stays inline.
#define BFME_STRINGBASE_PUBLIC_DTOR
#include "../../../../reference/shims/bfme2_ascii/unicode_string.h"



#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

struct Rva005EF096Inner
{
	char m_pad8[8];
	char m_name[1];
};

struct Rva005EF096Outer
{
	Rva005EF096Inner *m_ptr;
};

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &, const UnicodeString &, bool);
};

class Rva00222A8BTarget
{
};

class Rva00222A8BTarget;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

#include "../../Include/GameClient/GameText.h"

extern GameTextInterface *TheGameText;

void __cdecl StrategicHUD::SetCommandPointsString(int level, Rva005EF096Outer *outer, int a, int b)
{
	UnicodeString commandPointsText;
	Bool exists;
	UnicodeString fetched = TheGameText->fetch("STRATEGICHUD:StatsCommandPoints", &exists);
	if (exists)
	{
		const wchar_t *fmt = fetched.str();
		commandPointsText.format(fmt, a, b);
	}
	AsciiString key;
	const char *mid = outer->m_ptr ? outer->m_ptr->m_name : "";
	key.format("APT:_level%u.%s_CommandPoints", level, mid);
	g_bfmeAptWindowManager->bfmeSetText(key, commandPointsText, true);
}
