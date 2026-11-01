// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?SetBuildingNameString@StrategicHUD@@YAXHPAURva005F066COuter@@ABVUnicodeString@@@Z @0x005F066C 103B caller 0x005F0C54, format APT:_level BuildingName via 0x00038150
#include "../../Include/Common/BfmeStringData.h"

#include "ascii_string.h"

#include "unicode_string.h"
struct Rva005F066COuter;
class UnicodeString;
namespace StrategicHUD
{
	void __cdecl SetBuildingNameString(int level, Rva005F066COuter *outer, const UnicodeString &text);
}

struct Rva005F066CInner
{
	char m_pad8[8];
	char m_name[1];
};

struct Rva005F066COuter
{
	Rva005F066CInner *m_ptr;
};

#include "../../../Libraries/Source/Apt/BfmeAptWindowManager.h"

extern BfmeAptWindowManager *g_bfmeAptWindowManager;

void __cdecl StrategicHUD::SetBuildingNameString(int level, Rva005F066COuter *outer, const UnicodeString &text)
{
	AsciiString key;
	const char *mid = outer->m_ptr ? outer->m_ptr->m_name : "";
	key.format("APT:_level%u.%s_BuildingName", level, mid);
	g_bfmeAptWindowManager->bfmeSetText(key, text, true);
}
