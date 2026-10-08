// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?Rva0057A51CSet@@YAXHPAPAURva0057A51CTeam@@H@Z @0x0057A51C 140B.
// Free Apt TurnNumber setter: team name lookup then format APT:_level%u.%s_TurnNumber plus Unicode int format then bfmeSetText false.
// Evidence: unlock lane plus callers 0x0057A851 0x0057B90B plus precedent Rva0057A685Apt plus globals TheRva00222A8BTarget g_Rva0107301CEmptyString g_Va007C9260 plus string APT:_level%u.%s_TurnNumber.
#include "ascii_string.h"
#include "unicode_string.h"

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &, const UnicodeString &, bool);
};

class Rva00222A8BTarget
{
};

extern Rva00222A8BTarget *TheRva00222A8BTarget;
extern const unsigned short g_Va007C9260[];

struct Rva0057A51CTeam
{
	char m_pad8[8];
	char m_name[1];
};

void Rva0057A51CSet(int level, Rva0057A51CTeam **ppTeam, int turn)
{
	AsciiString key;
	Rva0057A51CTeam *team = *ppTeam;
	const char *mid = team ? team->m_name : "";
	key.format("APT:_level%u.%s_TurnNumber", level, mid);
	UnicodeString value;
	value.format(g_Va007C9260, turn);
	((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, value, false);
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?g_Va007C9260@@3QBGB=??_C@_15KNBIKKIN@?$AA?$CF?$AAd?$AA?$AA@")
