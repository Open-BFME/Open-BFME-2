// cl: /Ireference/shims/bfme2_ascii /GX /DNDEBUG /MD
//
// ?Rva004DBFF1Parse@@YAXPAVINI@@PAX1PBX@Z, retail 0x004DBFF1 (145B): the
// SkirmishAIHeuristic FieldParse proc (row 0x00BFA878, store +0x98). The
// next token is read as an AsciiString and matched, by AsciiString compare
// against each of the four names at VA 0x00DCFC24, to its index; -1 is stored
// when nothing matches. Name address-derived.

#include "ascii_string.h"

#define NULL 0

class INI
{
public:
	AsciiString getNextAsciiString();
};

// The existing four-entry heuristic parser's target table, VA 0x00DCFC24.
// Supply its previously unowned definition with the exact target strings.
const char *g_00DCFC24[] = {
	"AI_UPGRADEHEURISTIC_IMPORTANT",
	"AI_UPGRADEHEURISTIC_BOILINGOIL",
	"AI_UPGRADEHEURISTIC_FACTORY_UNITUNLOCK",
	"AI_UPGRADEHEURISTIC_FORTRESS"
};

// Also used by the matched parseToken at 0x0058A5C7. Target table
// VA 0x00DD3068 has exactly these 41 entries; these are target strings,
// not a donor enum layout or a claim about the original variable name.
const char *g_00DD3068[] = {
	"AI_SPECIAL_POWER_BASIC_SELF_BUFF",
	"AI_SPECIAL_POWER_CAPTURE_BUILDING",
	"AI_SPECIAL_POWER_ELENDIL",
	"AI_SPECIAL_POWER_ENEMY_TYPE_KILLER",
	"AI_SPECIAL_POWER_ENEMY_TYPE_KILLER_RANGED",
	"AI_SPECIAL_POWER_ENEMY_TYPE_KILLER_STRUCTURES",
	"AI_SPECIAL_POWER_GANDALF_WIZARD_BLAST",
	"AI_SPECIAL_POWER_GIVEXP_AOE",
	"AI_SPECIAL_POWER_RANGED_AOE_ATTACK",
	"AI_SPECIAL_POWER_TOGGLE_MOUNTED",
	"AI_SPECIAL_POWER_SELFAOEHEALHEROS",
	"AI_SPECIAL_POWER_TARGETAOE_SUMMON",
	"AI_SPECIAL_POWER_LEGOLAS_ARROWWIND",
	"AI_SPECIAL_POWER_LEGOLAS_TRAINARCHERS",
	"AI_SPECIAL_POWER_GOBLINKING_BATTLEFRENZY",
	"AI_SPECIAL_POWER_GOBLINKING_CALLOFTHEDEEP",
	"AI_SPECIAL_POWER_GOBLINKING_MOUNTED",
	"AI_SPECIAL_POWER_HEAL_AOE",
	"AI_SPECIAL_POWER_TOGGLE_MELEE_AND_RANGE",
	"AI_SPECIAL_POWER_TOGGLE_SIEGE",
	"AI_SPECIAL_POWER_CHARGE",
	"AI_SPELLBOOK_ALWAYS_FIRE",
	"AI_SPELLBOOK_ASSIST_BATTLE_BUFF",
	"AI_SPELLBOOK_ASSIST_BATTLE_DEBUFF",
	"AI_SPELLBOOK_ARMY_BREAKER",
	"AI_SPELLBOOK_CAPTURE_CREEP",
	"AI_SPELLBOOK_HEAL",
	"AI_SPELLBOOK_STRUCTURE_BREAKER",
	"AI_SPELLBOOK_STRUCTURE_BREAKER_PREF_WALLS",
	"AI_SPELLBOOK_ENSHROUDINGMIST",
	"AI_SPELLBOOK_BUFFTERRAIN",
	"AI_SPELLBOOK_REBUILD",
	"AI_SPELLBOOK_BUFFECONOMYBUILDING",
	"AI_SPELLBOOK_CALLTHEHORDE",
	"AI_SPELLBOOK_SHROUD_REVEAL",
	"AI_SPELLBOOK_TREE_KILLER",
	"AI_SPELLBOOK_STRUCTURE_BASEKILL",
	"AI_SPELLBOOK_CITADEL",
	"AI_SPECIAL_POWER_STANCEBATTLE",
	"AI_SPECIAL_POWER_STANCEAGGRESSIVE",
	"AI_SPECIAL_POWER_STANCEHOLDGROUND"
};

// AsciiString view whose text compare is declared nonthrowing, so the
// temporary needs no unwind state (retail registers none); the spelling
// resolves to the rowed StringBase<char>::compare(const char *) at 0x000069B1.
class Rva004DBFF1Name : public AsciiString
{
public:
	Rva004DBFF1Name(const char *s) : AsciiString(s) {}
	int compareText(const char *text) const throw();
};

static inline int Rva004DBFF1Index(const char *name)
{
	int result = -1;
	if (name)
	{
		for (int i = 0; i < 4; ++i)
		{
			if (Rva004DBFF1Name(g_00DCFC24[i]).compareText(name) == 0)
			{
				result = i;
				break;
			}
		}
	}
	return result;
}

// ?Rva004DBFF1Parse@@YAXPAVINI@@PAX1PBX@Z
void Rva004DBFF1Parse(INI *ini, void *, void *store, const void *)
{
	*(int *)store = Rva004DBFF1Index(ini->getNextAsciiString().str());
}

static inline int Rva0058A617Index(const char *name)
{
	int result = -1;
	if (name)
	{
		for (int i = 0; i < 41; ++i)
		{
			if (Rva004DBFF1Name(g_00DD3068[i]).compareText(name) == 0)
			{
				result = i;
				break;
			}
		}
	}
	return result;
}

// Retail 0x0058A617..0x0058A6A8, 145B: FieldParse table at VA
// 0x00C56ED8 registers this cdecl parser as SpecialPowerAIType, store +0xC,
// in AISpecialPowerUpdateModuleData's rowed field-parse unit. The target
// inlines the neighbouring 0x0058A5C7 search over the same table. The
// original parser name is unresolved; identity here is the registered field.
void Rva0058A617Parse(INI *ini, void *, void *store, const void *)
{
	*(int *)store = Rva0058A617Index(ini->getNextAsciiString().str());
}
