// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva00414081@Rva00414081@@QAEXPAVINI@@@Z, retail 0x00414081, 18 bytes.
// INI parse wrapper over rowed ?initFromINI@INI@@QAEXPAXPBUFieldParse@@@Z with table 0x00C39EB8.
// Caller at 0x004142D7 in 0x0041428F passes INI in esi and object in ecx; same 18B shape as rowed 0x00415C56.
// Owner unproven so honest-address class Rva00414081.
class INI;
#include "../../Include/Common/INI/FieldParse.h"

// The two parsers retail's bonus-map record reaches, both already-rowed bodies:
// the Sides -> side-flag parser (0x002E2612) and the bonus parser (0x00414009)
// in Code/GameEngine/Source/Common/INI/LivingWorldBonusMapParsers.cpp.
void Rva002E2612Parse(INI *ini, void *instance, void *store, const void *userData);
void Rva00414009Parse(INI *ini, void *instance, void *store, const void *userData);

// Retail VA 0x00C39EB8 (.rdata, file offset 0x008339B8): the bonus map's two
// field records - Sides through the rowed side-flag parser at +0 and Bonus
// through the rowed bonus parser at +0xC - then the zero sentinel; the 48-byte
// extent is the ledger's own bound.
// Symbol ?g_00C39EB8@@3QBUFieldParse@@B, transcribed below.
extern const struct FieldParse g_00C39EB8[] =
{
	{ "Sides", &Rva002E2612Parse, 0, 0x0 },
	{ "Bonus", &Rva00414009Parse, 0, 0xC },
	{ 0, 0, 0, 0 }
};
class INI
{
public:
	void initFromINI(void *what, const struct FieldParse *table);
};
class Rva00414081
{
public:
	void rva00414081(INI *ini);
};
void Rva00414081::rva00414081(INI *ini)
{
	ini->initFromINI(this, g_00C39EB8);
}
