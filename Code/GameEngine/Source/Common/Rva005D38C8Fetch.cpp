// cl: /MD /EHsc
// StrategicHUD::FormatCommandPointsString retail 0x005D38C8 158B and
// StrategicHUD::SetCommandPointsString retail 0x005D3966 132B: WorldBuilder
// names both (StrategicHUDSelectionUIImpl.cpp; SetCommandPointsString assert
// line 52, the _CP key). The clip name stays the opaque holder this unit
// already models.
// Evidence: unlock; TheGameText fetch slot 0x3C STRATEGICHUD:ArmyUnitSwapperCP; UnicodeString format 0x006CB5D0; releaseBuffer 0x00036E70; copy ctor 0x00037050; caller 0x005D3966
typedef unsigned short wchar_t;
typedef bool Bool;
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

template <typename T> class StringBase;
class UnicodeString;
struct Rva005D2FD0Outer;
namespace StrategicHUD
{
	UnicodeString FormatCommandPointsString(int a, int b);
	void SetCommandPointsString(int level, Rva005D2FD0Outer *outer, int a, int b);
}

#include "../../../../reference/shims/bfme2_ascii/unicode_string.h"

#include "../../Include/Common/Rva005D2FD0Inner.h"

struct Rva005D2FD0Outer
{
	Rva005D2FD0Inner *m_ptr;
};

#include "../../../Libraries/Source/Apt/BfmeAptWindowManager.h"

extern BfmeAptWindowManager *g_bfmeAptWindowManager;

#include "../../Include/GameClient/GameText.h"

extern GameTextInterface *TheGameText;

UnicodeString StrategicHUD::FormatCommandPointsString(int a, int b)
{
	UnicodeString formattedText;
	if (b >= 0) {
		Bool exists;
		UnicodeString fetched = TheGameText->fetch("STRATEGICHUD:ArmyUnitSwapperCP", &exists);
		if (exists) {
			const wchar_t *fmt = fetched.str();
			formattedText.format(fmt, a, b);
		}
	}
	return formattedText;
}

// StrategicHUD::SetCommandPointsString retail 0x005D3966 132B
// Evidence: chain from 0x005D38C8; APT:_level%u.%s_CP via 0x00038150; bfmeSetText pin 0x00225301; release wide 0x00036E70 ansi 0x00036410; callers 0x005D3A0A 0x005D3F46
void StrategicHUD::SetCommandPointsString(int level, Rva005D2FD0Outer *outer, int a, int b)
{
	AsciiString key;
	const char *mid = outer->m_ptr ? outer->m_ptr->m_name : "";
	key.format("APT:_level%u.%s_CP", level, mid);
	g_bfmeAptWindowManager->bfmeSetText(key, FormatCommandPointsString(a, b), true);
}
