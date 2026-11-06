// cl: /MD
// ?Rva0050AD97BuildFieldParse@@YAXAAVMultiIniFieldParse@@@Z retail 0x0050AD97 34B two adds.
// Evidence: callees rowed 0x00507552 0x0002BC6E; data VA 0x00864B60; caller 0x0050ADB9 pushes one parse ref.
#include "../../../../Include/Common/INI/FieldParse.h"


int Rva00507552Get();

#include "../../../../Include/Common/INI/INI.h"

// BFME 2's death type names (GameLogic/Damage.h's TheDeathNames, a static in every unit that
// includes it), this unit's copy at retail .data 0x009D0FA0: 24 names and a null.
static const char *TheDeathNames[] =
{
	"NORMAL",
	"NONE",
	"CRUSHED",
	"BURNED",
	"EXPLODED",
	"POISONED",
	"TOPPLED",
	"FLOODED",
	"SUICIDED",
	"LASERED",
	"DETONATED",
	"SPLATTED",
	"POISONED_BETA",
	"EXTRA_2",
	"EXTRA_3",
	"EXTRA_4",
	"EXTRA_5",
	"EXTRA_6",
	"EXTRA_7",
	"EXTRA_8",
	"KNOCKBACK",
	"SUPERNATURAL",
	"FADED",
	"SLAUGHTERED",
	0
};

void Rva002567EAParse(INI *ini, void *instance, void *store, const void *userData);

// The table at retail .rdata 0x00864B60: four entries and the null entry, read from retail's
// words (the rowed INI::parseInt 0x0002EF56, Rva002567EAParse 0x002567EA and
// INI::parseIndexList 0x0002EC4E).
static const FieldParse s_table0050AD97[] =
{
	{ "KillCount", INI::parseInt, 0, 0x128 },
	{ "KillKindof", Rva002567EAParse, 0, 0x12C },
	{ "KillKindofNot", Rva002567EAParse, 0, 0x148 },
	{ "DeathType", INI::parseIndexList, TheDeathNames, 0x164 },
	{ 0, 0, 0, 0 }
};

void Rva0050AD97BuildFieldParse(MultiIniFieldParse &parse)
{
	parse.add((const FieldParse *)Rva00507552Get(), 0);
	parse.add(s_table0050AD97, 0);
}
